package easy;

public class JudgeCircle {
    public boolean judgeCircle(String moves) {
        if (moves.isEmpty()) return true;
        int[] counts = new int[4];
        char[] movesArray = moves.toCharArray();
        for(var move : movesArray){
            if(move=='U'){
                counts[0]++;
            }else if(move=='D'){
                counts[1]++;
            }else if(move=='L'){
                counts[2]++;
            }else{
                counts[3]++;
            }
        }
        if(counts[0]==counts[1]  && counts[2]==counts[3]) return true;
        return false;
    }
}
