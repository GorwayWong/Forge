#include <vector>
#include <limits.h>

class _414Solution
{
public:
    void switchNums(int &num1, int &num2)
    {
        int temp;
        temp = num1;
        num1 = num2;
        num2 = temp;
    }
    int thirdMax(std::vector<int> &nums)
    {
        long first = LONG_MIN, second = LONG_MIN, third = LONG_MIN;
        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] > first)
            {
                third=second;
                second = first;
                first = nums[i];
            }
            else if (nums[i]<first && nums[i] > second)
            {
                third = second;
                second = nums[i];
            }else if(nums[i]<second && nums[i]>third){
                third = nums[i];
            }
        }
        if(third == LONG_MIN) return first;
        return third;
    }
};