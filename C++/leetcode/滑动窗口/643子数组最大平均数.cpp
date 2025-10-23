#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <vector>
#include <algorithm>

class _643Solution
{
public:
    double findMaxAverage(std::vector<int> &nums, int k)
    {
        double maxAverage = -999999;
        int left, right;
        double sum = 0;
        for (int i = 0; i < nums.size(); i++)
        {
            right = i;
            sum += nums[right];
            left = right - k + 1;
            if(left < 0) continue;
            maxAverage = std::max(maxAverage,sum/k);
            sum-=nums[left];
        }
        return maxAverage;
    }
};