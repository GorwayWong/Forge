class _374Solution {
public:
    int guess(int n);
    int guessNumber(int n) {
        long left=0,right = n;
        long mid;
        while(left<=right){
            mid = (left+right)/2;
            if(guess(mid)==1) left = mid+1;
            else if(guess(mid)==-1) right=mid-1;
            else{
                return mid;
            }
        }
        return n;
    }
};