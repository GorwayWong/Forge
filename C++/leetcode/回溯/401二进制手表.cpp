#include<vector>
#include<string>

class Solution {
public:
    std::vector<std::string> ans;
    int times[10] = {1,2,4,8,1,2,4,8,16,32};
    std::vector<std::string> readBinaryWatch(int turnedOn) {
        track(turnedOn,0,0,0);
        return ans;
    }

    void track(int num,int hour,int minute,int cur){
        if(hour>11 || minute > 59) return;
        std::string timeStr;
        if(num == 0){
            if(hour==0){
                timeStr+="0:";
            }else{
                timeStr+=std::to_string(hour);
                timeStr+=":";
            }

            if(minute<10){
                timeStr+="0";
            }
            timeStr+=std::to_string(minute);
            ans.push_back(timeStr);
        }else{
            for(int i = cur;i<10;i++){
                if(i<=3){
                    track(num-1,hour+times[i],minute,i+1);//是i+1不是cur+1
                }else{
                    track(num-1,hour,minute+times[i],i+1);
                }
            }
        }
    }
};