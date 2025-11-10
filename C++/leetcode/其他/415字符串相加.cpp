#include <string>
#include<algorithm>

//用双指针做更好
class _415Solution
{
public:
    std::string addStrings(std::string num1, std::string num2)
    {
        std::string ans, longNum, shortNum;
        int length1 = num1.length();
        int length2 = num2.length();
        int longLen, shortLen;
        int sumNum, stepIn = 0;
        if (length1 > length2)
        {
            longNum = num1;
            shortNum = num2;
            longLen = length1;
            shortLen = length2;
        }
        else
        {
            longNum = num2;
            shortNum = num1;
            longLen = length2;
            shortLen = length1;
        }
        for (int i = 1; i <= shortLen; i++)
        {
            sumNum = longNum[longLen - i] - '0' + shortNum[shortLen - i] - '0' + stepIn;
            if (sumNum >= 10)
            {
                sumNum %= 10;
                stepIn = 1;
            }
            else
            {
                stepIn = 0;
            }
            ans += std::to_string(sumNum);
        }
        if (stepIn == 1)
        {
            for (int i = longLen - shortLen - 1; i >= 0; i--)
            {
                sumNum = longNum[i] - '0' + stepIn;
                if (sumNum >= 10)
                {
                    sumNum %= 10;
                    stepIn = 1;
                }
                else
                {
                    stepIn = 0;
                }
                ans += std::to_string(sumNum);
            }
            if(stepIn==1) ans+="1";
        }else{
            for(int i=longLen-shortLen-1;i>=0;i--){
                ans+=std::to_string(longNum[i] - '0');
            }
        }
        std::reverse(ans.begin(),ans.end());
        return ans;
    }
};