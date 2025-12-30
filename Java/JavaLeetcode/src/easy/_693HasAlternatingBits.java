package easy;

public class _693HasAlternatingBits {
    public boolean hasAlternatingBits(int n) {
        int pre=n&1;
        int cur;
        n=n>>1;
        while(n!=0){
            cur = n&1;
            if(pre==cur) return false;
            pre=cur;
            n=n>>1;
        }
        return true;
    }
}
