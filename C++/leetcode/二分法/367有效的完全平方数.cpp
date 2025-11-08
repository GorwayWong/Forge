#include<stdio.h>

class _367Solution {
public:
    bool isPerfectSquare(int num) {
        long left = 0;
        long right = num;
        long mid;
        while(left<=right){//必须要有等于号，不然等于的情况直接返回了false
            mid = (right+left)/2;
            if(mid*mid>num) right = mid-1;
            else if(mid*mid < num) left = mid+1;
            else{
                return mid;
            }
        }
        return false;
    }
};