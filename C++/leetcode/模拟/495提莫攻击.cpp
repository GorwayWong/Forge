#include<vector>
class _495Solution {
public:
    int findPoisonedDuration(std::vector<int>& timeSeries, int duration) {
        int count = 0;
        int lastEnd = -1;
        int end;
        for(auto timeTick:timeSeries){
            if(timeTick>lastEnd){
                count+=duration;
            }else{
                count+=(timeTick+duration-1) - lastEnd;
            }
            lastEnd = timeTick+duration-1;
        }
        return count;
    }
};