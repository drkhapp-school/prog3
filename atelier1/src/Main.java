import java.io.EOFException;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.util.Arrays;
import java.util.List;

public class Main {


    public static void main(String[] args) throws IOException {
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
            if (Arrays.asList((args)).contains("-l")) {
                length = Integer.parseInt(args[argList.indexOf("-l") + 1]);
                if (length <= 0 || length > file.length() - offset) printUsage();
            } else {
                length = file.length() - offset;
            }

        } catch (IOException e) {
            System.out.println(e);
            printUsage();
            return;
        }
        printData(file, offset, length);
    }

    public static void printData(RandomAccessFile file, long offset, long length) throws IOException {
        String address;
        String line = "";
        String ascii = "";
        byte newline = 10;

        System.out.println("\u001B[33m             0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f  ASCII");
        
        file.seek(offset);
        while (file.getFilePointer() < length) {
            //TODO: make this shit work

            if (file.getFilePointer() % 16 == 0) {
                address = "0x0000" + (file.getFilePointer() / 16 - 1) + 0;

                if (!line.trim().isEmpty())
                System.out.printf("\u001B[33m %s \u001B[36m  %s\u001B[37m %s%n", address, line, ascii);

                line = "";
                ascii = "";
            }
        }
    }


    public static void printUsage() {
        System.out.println("Erreur de syntaxe");
        System.out.println("Usage: app.java -f filename.txt -o offset -l length");
        System.out.println("  -f    fichier, obligatoire");
        System.out.println("  -o    décalage, doit être >= 0 et < que la longueur du fichier");
        System.out.println("  -l    taille, doit être > 0 et < que la longueur du fichier");
        System.exit(1);
    }

}
