import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

public class MagicSquares {
    public static boolean testMagic(String pathName) throws IOException {
        // Open the file
        BufferedReader reader = new BufferedReader(new FileReader(pathName));

        boolean isMagic = true;
        int lastSum = -1;
        
        // For each line in the file ...
        String line;
        ArrayList<String[]> matrix = new ArrayList<>();
        while ((line = reader.readLine()) != null) {
            // ... sum each row of numbers
            String[] parts = line.split("\t");
            matrix.add(parts);
            int sum = 0;
            for (String part : parts) {
                sum += Integer.parseInt(part.trim());
            }

            if (lastSum == -1) {
                // If this is the first row, remember the sum
                lastSum = sum;
            } else if (lastSum != sum) {
                // if the sums don't match, it isn't magic, so stop reading
                isMagic = false;
                break;
            }
        }
        lastSum = -1;
        int lineSum = 0;
        int diagonal1 = 0;
        int diagonal2 = 0;
        for (int i = 0; i < matrix.size(); i++) {
            // 第i列
            lineSum = 0;
            for (int j = 0; j < matrix.size(); j++) {
                lineSum += Integer.parseInt(matrix.get(j)[i]);
                if(i==j){
                    diagonal1 += Integer.parseInt(matrix.get(j)[i]);
                }
                if(i+j==matrix.size()-1){
                    diagonal2 += Integer.parseInt(matrix.get(j)[i]);
                }
            }
            if (lastSum == -1) {
                // If this is the first line, remember the sum
                lastSum = lineSum;
            } else if (lastSum != lineSum) {
                // if the sums don't match, it isn't magic, so stop reading
                isMagic = false;
                System.out.println("The line sum is different at " + i);
                break;
            }
        }
        if (diagonal1 != lastSum || diagonal2 != lastSum) {
            System.out.println("The diagonal is not the same "+diagonal1+" "+diagonal2);
            isMagic = false;
        }
        reader.close();
        return isMagic;
    }

    public static void main(String[] args) throws IOException {
        String[] fileNames = {"Mercury.txt", "Luna.txt"};
        for (String fileName : fileNames) {
            System.out.println(fileName + " is magic? " + testMagic(fileName));
        }
    }
}
