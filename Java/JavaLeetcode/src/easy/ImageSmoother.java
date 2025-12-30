package easy;

public class ImageSmoother {
    public boolean isLegal(int i,int j,int rows,int cols){
        return i < rows && j < cols && i >= 0 && j >= 0;
    }
    public int[][] imageSmoother(int[][] img) {
        int rows = img.length;
        int cols = img[0].length;
        int[][] res = new int[rows][cols];
        int sum = 0;
        int count = 0;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                sum = img[i][j];
                count = 1;
                if(isLegal(i-1,j-1,rows,cols)){
                    sum+=img[i-1][j-1];
                    count++;
                }
                if(isLegal(i-1,j,rows,cols)){
                    sum+=img[i-1][j];
                    count++;
                }
                if(isLegal(i-1,j+1,rows,cols)){
                    sum+=img[i-1][j+1];
                    count++;
                }
                if(isLegal(i,j-1,rows,cols)){
                    sum+=img[i][j-1];
                    count++;
                }
                if(isLegal(i,j+1,rows,cols)){
                    sum+=img[i][j+1];
                    count++;
                }
                if(isLegal(i+1,j-1,rows,cols)){
                    sum+=img[i+1][j-1];
                    count++;
                }
                if(isLegal(i+1,j,rows,cols)){
                    sum+=img[i+1][j];
                    count++;
                }
                if(isLegal(i+1,j+1,rows,cols)){
                    sum+=img[i+1][j+1];
                    count++;
                }
                res[i][j]=sum/count;
            }
        }
        return res;
    }
}
