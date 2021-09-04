import java.io.IOException;
import java.io.RandomAccessFile;
import java.util.Arrays;
import java.util.List;

public class Main {

    public static void main(String[] args) {
        List<String> argList = Arrays.asList(args);
        RandomAccessFile file;
        long offset = 0;
        long length;

        try {
            // Fichier
            if (!argList.contains("-f"))
                throw new IOException();
            String filename = args[argList.indexOf("-f") + 1];
            file = new RandomAccessFile(filename, "r");

            // Décalage
            if (argList.contains("-o")) {
                offset = Integer.parseInt(args[argList.indexOf("-o") + 1]);
                if (offset < 0 || offset > file.length())
                    printUsage();
            }

            // Longueur
            if (argList.contains("-l")) {
                length = Integer.parseInt(args[argList.indexOf("-l") + 1]);
                if (length <= 0 || length > file.length() - offset)
                    printUsage();
            } else
                length = file.length() - offset;

            printData(file, offset, length);
        } catch (NumberFormatException | IOException e) {
            printUsage();
        }
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

        String[] hexArray = new String[(int) file.length()];
        Arrays.fill(hexArray, "  ");

        char[] ascArray = new char[(int) file.length()];
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
        System.out.println("usage: app.java [-o <value>] [-l <value>] -f <fichier>");
        System.out.println("    -f    fichier, obligatoire");
        System.out.println("    -o    decalage, doit etre >= 0 et < que la longueur du fichier");
        System.out.println("    -l    taille, doit etre > 0 et < que la longueur du fichier");
        System.exit(1);
    }
}
