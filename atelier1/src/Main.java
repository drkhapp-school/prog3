import java.io.IOException;
import java.io.RandomAccessFile;
import java.util.Arrays;
import java.util.List;

public class Main {

    public static void main(String[] args) {
        // TODO: Gestion du fichier.

        List<String> argList = Arrays.asList(args);
        RandomAccessFile file;
        long offset = 0;
        long length;

        // Gestion d'arguments
        // Fichier
        try {
            // fichier
            if (!argList.contains("-f")) throw new IOException();
            String filename = args[argList.indexOf("-f") + 1];
            file = new RandomAccessFile(filename, "r");

            // offset
            if (argList.contains("-o")) {
                offset = Integer.parseInt(args[argList.indexOf("-o") + 1]);
                if (offset < 0 || offset > file.length()) printUsage();
            }

            // length
            if (argList.contains("-l")) {
                length = Integer.parseInt(args[argList.indexOf("-l") + 1]);
                if (length <= 0 || length > file.length() - offset) printUsage();
            } else {
                length = file.length() - offset;
            }

            if (argList.contains("-s")) {
                byte minLength = 4;
                try {
                    minLength = Byte.parseByte(args[argList.indexOf("-s") +1]);
                } catch(Exception ignored) { }

                printStrings(file, length, minLength);
            } else {
                printData(file, offset, length);
            }
        } catch (NumberFormatException | IOException e) {
            printUsage();
        }
    }

    public static void printStrings(RandomAccessFile file, long length, byte minLength) throws IOException {
        // TODO: Affichage des chaînes de caractères.
        String[] hexArray = new String[(int)length];
        char[] ascArray = new char[(int)length];

        for (int i = 0; i < length; i++) {
            byte[] bytes = new byte[minLength];
            int value = file.read(bytes);
            hexArray[i] = String.format("%02x", value);

            ascArray[i] = (char) value;
        }



        System.out.println(Arrays.toString(hexArray));
    }


    public static void printData(RandomAccessFile file, long offset, long length) throws IOException {
        String address;
        int lineCount = (int) (length / 16) + 1;
        int[] illegal = {10, 13};

        String[] hexArray = new String[lineCount * 16];
        Arrays.fill(hexArray, "  ");

        char[] ascArray = new char[lineCount * 16];
        Arrays.fill(ascArray, ' ');

        file.seek(offset);
        for (int i = (int) offset % 8; i < length; i++) {
            int value = file.read();
            hexArray[i] = String.format("%02x", value);

            if (Arrays.stream(illegal).anyMatch(x -> x == value)) ascArray[i] = '.';
            else ascArray[i] = (char) value;
        }

        System.out.println("\u001B[33m             0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f  ASCII");
        for (int i = 0; i < lineCount; i++) {
            StringBuilder hexAddress = new StringBuilder();
            char[] ascText = new char[16];

            for (int j = 0; j < 16; j++) {
                hexAddress.append(hexArray[i * 16 + j]).append(" ");
            }

            System.arraycopy(ascArray, i * 16, ascText, 0, 16);

            address = "0x0000" + i + "0";
            System.out.printf("\u001B[33m %s \u001B[36m  %s\u001B[37m %s%n", address, hexAddress, new String(ascText));
        }

    }


    public static void printUsage() {
        System.out.println("Usage: app.java -f filename.txt -o offset -l length");
        System.out.println("  -f    fichier, obligatoire");
        System.out.println("  -o    décalage, doit être >= 0 et < que la longueur du fichier");
        System.out.println("  -l    taille, doit être > 0 et < que la longueur du fichier");
        System.exit(1);
    }

}
