package easy;

public class CountBinarySubstrings {
    //抄来的代码 很巧妙地兼顾了开始和结束的情况
    public int countBinarySubstrings(String s) {
        int count = 0;
        int length = s.length();;
        int preBlock = 0;
        int curBlock = 0;
        char lastChar = '-';
        s+='?';
        for(char c:s.toCharArray()){
            if(lastChar!=c){
                lastChar = c;
                count+=Integer.min(preBlock,curBlock);
                preBlock = curBlock;
                curBlock = 0;
            }
            curBlock++;
        }
        return count;
    }
}
