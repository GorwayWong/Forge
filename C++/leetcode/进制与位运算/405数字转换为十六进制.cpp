#include<string>
#include<algorithm>
#include<cmath>

class _405Solution {
public:
    std::string toHex(int num) {
        std::string ans;
        long numTemp = num;
        int singleNumber;
        if(num<0) numTemp = pow(2,32) + num;
        /*
        关于这里为什么加2^32次方的一点思考：
        `先枚举几个负数的补码值： -1对应0xFFFFFFFF,（看作0xFFFFFFFF+1-1）；
        -2对应0xFFFFFFFE,（看作0xFFFFFFFF+1-2）。
        我们可以发现，对于一个给定的负数，只需要将其加上0xFFFFFFFF+1,再减去该负数的绝对值即可得到该负数对应的补码值。
        */
        while(numTemp!=0){
            singleNumber = numTemp %16;
            if(singleNumber<10){
                ans+=std::to_string(singleNumber);
            }else if(singleNumber==10){
                ans+="a";
            }else if(singleNumber==11){
                ans+="b";
            }else if(singleNumber==12){
                ans+="c";
            }else if(singleNumber==13){
                ans+="d";
            }else if(singleNumber==14){
                ans+="e";
            }else{
                ans+="f";
            }
            numTemp/=16;
        }
        std::reverse(ans.begin(),ans.end());
        return ans;
    }
};