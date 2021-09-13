import java.io.IOException;
import java.io.RandomAccessFile;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class Main {

    public static void main(String[] args) {
        List<String> argList = Arrays.asList(args);
        RandomAccessFile file;
        long offset = 0;
        long length;

        try {
            // Vérification des obligations
            // Aucun fichier
            if (!argList.contains("-f"))
                throw new IllegalArgumentException();
            // Option -s et & -i en même temps
            if (argList.contains("-s") && argList.contains("-i"))
                throw new IllegalArgumentException();

            // Fichier
            String filename = args[argList.indexOf("-f") + 1];
            file = new RandomAccessFile(filename, "r");

            // Décalage
            if (argList.contains("-o")) {
                String arg = args[argList.indexOf("-o") + 1];

                if (arg.startsWith("0x"))
                    offset = Long.parseLong(arg.replace("0x", ""), 16);
                else
                    offset = Long.parseLong(arg);

                if (offset < 0 || offset > file.length())
                    printUsage();
            }

            // Longueur
            if (argList.contains("-l")) {
                String arg = args[argList.indexOf("-l") + 1];

                if (arg.startsWith("0x"))
                    length = Long.parseLong(arg.replace("0x", ""), 16);
                else
                    length = Long.parseLong(arg);

                if (length <= 0 || length > file.length() - offset)
                    printUsage();
            } else
                length = file.length() - offset;

            // printString
            if (argList.contains("-s")) {
                byte minLength = 4;
                try {
                    minLength = Byte.parseByte(args[argList.indexOf("-s") + 1]);
                } catch (NumberFormatException | ArrayIndexOutOfBoundsException ignored) {
                }

                printStrings(file, offset, length, minLength);
            } else if (argList.contains("-i")) {
                printFormat(file);
            } else {
                printData(file, offset, length);
            }

        } catch (IOException | IllegalArgumentException | ArrayIndexOutOfBoundsException e) {
            printUsage();
        }
    }

    /**
     * Imprimer le système d'exploitation et le processeur cible d'un executable
     *
     * @param file le programme
     */
    public static void printFormat(RandomAccessFile file) throws IOException {
        byte[] windows = new byte[]{0x4d, 0x5a};
        byte[] mac32 = new byte[]{(byte) 0xce, (byte) 0xfa, (byte) 0xed, (byte) 0xfe};
        byte[] mac64 = new byte[]{(byte) 0xcf, (byte) 0xfa, (byte) 0xed, (byte) 0xfe};
        byte[] macuni = new byte[]{(byte) 0xbe, (byte) 0xba, (byte) 0xfe, (byte) 0xca};
        byte[] linux = new byte[]{0x7f, 0x45, 0x4c, 0x46};
        byte[] input = new byte[4];
        String os = "Unknown";
        String architecture = "Unknown";

        file.read(input);

        /// OS du fichier
        if (Arrays.equals(new byte[]{input[1], input[2]}, windows))
            os = "Windows";
        else if (Arrays.equals(input, mac32))
            os = "macOS 32-bit";
        else if (Arrays.equals(input, mac64))
            os = "macOS 64-bit";
        else if (Arrays.equals(input, macuni))
            os = "macOS Universal";
        else if (Arrays.equals(input, linux))
            os = "Linux";

        // Architecture du fichier selon l'OS
        // devnote: honnêtement je me suis compliqué trop la vie, mais ça marche™️
        switch (os) {
            case "Windows" -> {
                byte[] offset = new byte[4];
                byte[] type = new byte[2];
                byte[] x64 = new byte[]{0x64, (byte) 0x86};
                file.seek(0x3c);
                file.read(offset);

                ByteBuffer bb = ByteBuffer.wrap(offset).order(ByteOrder.LITTLE_ENDIAN);
                file.seek(bb.getInt() + 4);
                file.read(type);

                if (Arrays.equals(type, x64))
                    architecture = "x64";
            }

            case "macOS 32-bit", "macOS 64-bit", "macOS Universal" -> {
                byte[] type = new byte[4];
                byte[] x86_64 = new byte[]{0x07, 0x00, 0x00, 0x01};
                byte[] arm = new byte[]{0x0c, 0x00, 0x00, 0x00};
                file.seek(0x04);
                file.read(type);

                if (Arrays.equals(type, x86_64))
                    architecture = "x86_64";
                else if (Arrays.equals(type, arm))
                    architecture = "ARM";
            }

            case "Linux" -> {
                file.seek(0x12);
                switch (file.readByte()) {
                    case (byte) 0xb7 -> architecture = "ARM aarch64";
                    case (byte) 0x3e -> architecture = "x86-64";
                }
            }
        }

        System.out.println("OS: " + os);
        System.out.println("Machine: " + architecture);
    }

    /**
     * Imprime les chaînes de caractère
     *
     * @param file      le fichier à lire
     * @param length    la longueur des données à lire
     * @param minLength la longueur de la chaîne
     */
    public static void printStrings(RandomAccessFile file, long offset, long length, byte minLength) throws IOException {
        ArrayList<String> stringArray = new ArrayList<>();
        ArrayList<Byte> printable = new ArrayList<>();
        byte[] byteArray = new byte[(int) length];

        for (int i = 32; i < 127; i++) {
            printable.add((byte) i);
        }

        printable.add((byte) '\n');
        printable.add((byte) '\r');

        file.seek(offset);
        file.read(byteArray);

        for (int i = 0; i < length; i++) {
            if (printable.contains(byteArray[i])) {
                int buffer = 0;
                while (i + buffer < length && printable.contains(byteArray[i + buffer]))
                    buffer++;

                if (buffer >= minLength && (buffer >= length || byteArray[i + buffer] == 0)) {
                    byte[] newline = new byte[buffer];
                    System.arraycopy(byteArray, i, newline, 0, buffer);

                    String line = new String(newline, StandardCharsets.US_ASCII);

                    line = line.replace("\n", "\\n");
                    line = line.replace("\r", "\\r");

                    stringArray.add(line);
                }

                i += buffer;
            }
        }

        for (String line : stringArray) System.out.println(line);
    }

    /**
     * Imprime les données d'un fichier en valeur hexadécimal
     *
     * @param file   le fichier à lire
     * @param offset le nombre d'octets que l'on saute
     * @param length la longueur des données à lire
     */
    public static void printData(RandomAccessFile file, long offset, long length) throws IOException {
        int lineCount = (int) Math.ceil((double) (length + offset % 16) / 16);

        String[] hexArray = new String[lineCount * 16];
        Arrays.fill(hexArray, "  ");

        char[] ascArray = new char[lineCount * 16];
        Arrays.fill(ascArray, ' ');

        file.seek(offset);
        for (int i = (int) offset % 16; i < length + (offset % 16); i++) {
            int value = file.read();
            hexArray[i] = String.format("%02x", value);

            if (value <= 31 || value >= 127)
                ascArray[i] = '.';
            else
                ascArray[i] = (char) value;
        }

        System.out.println("\u001B[33m             0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f  ASCII");

        for (int i = 0; i < lineCount; i++) {
            StringBuilder hexValue = new StringBuilder();
            for (int j = 0; j < 16; j++)
                hexValue.append(hexArray[i * 16 + j]).append(" ");

            char[] ascText = new char[16];
            System.arraycopy(ascArray, i * 16, ascText, 0, 16);

            System.out.printf("\u001B[33m 0x%05x0 \u001B[36m  %s\u001B[37m %s%n", i + (offset / 16), hexValue,
                    new String(ascText));
        }
    }

    /**
     * Imprime comment utiliser l'application
     */
    public static void printUsage() {
        System.out.println("""
                usage: app.java [-o <value>] [-l <value>] -f <fichier> [-s [value] | -i]
                    -o  decalage, default: 0
                        doit etre >= 0 et < que la longueur du fichier
                    -l  taille, default: taille du fichier
                        doit etre > 0 et < que la longueur du fichier
                    -f  fichier, obligatoire
                    -s  string, default: 0
                        cherche une chaine de caractere (doit etre plus que 0)
                    -i  donne l'OS et l'architecture cible du fichier""");
        System.exit(1);
    }
}
