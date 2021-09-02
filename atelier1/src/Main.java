import java.io.IOException;
import java.io.RandomAccessFile;
import java.sql.Array;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Objects;
import java.util.stream.Collectors;

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
                    minLength = Byte.parseByte(args[argList.indexOf("-s") + 1]);
                } catch (NumberFormatException e) {
                    printUsage();
                } catch (ArrayIndexOutOfBoundsException ignored) {}

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
        ArrayList<Character> hexArray = new ArrayList<>();
        ArrayList<Byte> byteArray = new ArrayList<>();
        ArrayList<Byte> printable = new ArrayList<>();

        for (int i = 32; i < 127; i++) {
            printable.add((byte) i);
        }

        printable.add((byte) 10);

        for (int i = 0; i < length; i++) {
            byte value = file.readByte();
            if (printable.contains(value)) byteArray.add(i, value);
            else byteArray.add(i, null);
        }

        for (int i = 0; i < byteArray.size(); i++) {
            if (byteArray.get(i) != null) {
                int buffer = 0;
                while (buffer < minLength) {
                    if (byteArray.get(i + buffer) == null) break;
                    buffer++;
                }

                int buffer2 = 0;
                if (buffer == minLength) {
                    while (i + buffer2 != byteArray.size() && byteArray.get(i + buffer2) != null) {
                        hexArray.add((char) byteArray.get(i + buffer2).byteValue());
                        buffer2++;
                    }
                    hexArray.add('\n');
                }
                i = i + buffer + buffer2;
            }
        }

        System.out.println(hexArray.stream()
                .map(Object::toString)
                .collect(Collectors.joining()));
    }


    public static void printData(RandomAccessFile file, long offset, long length) throws IOException {
	    int lineCount = (int) Math.ceil((double) length / 16);

        String[] hexArray = new String[lineCount * 16];
        Arrays.fill(hexArray, "  ");

        char[] ascArray = new char[lineCount * 16];
        Arrays.fill(ascArray, ' ');

        file.seek(offset);
        for (int i = (int) offset % 8; i < length; i++) {
            int value = file.read();
            hexArray[i] = String.format("%02x", value);

            if (value <= 31 || value >= 127) ascArray[i] = '.';
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

            System.out.printf("\u001B[33m 0x%05x0 \u001B[36m  %s\u001B[37m %s%n", i, hexAddress, new String(ascText));
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
