#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include<algorithm>

class _2841Solution
{
public:
    long long maxSum(std::vector<int> &nums, int m, int k)
    {
        int left, right;
        long long _maxSum = 0;
        long long sum = 0;
        int n = nums.size();
        std::unordered_map<int, int> udmap;
        for (int i = 0; i < n; i++)
        {
            right = i;
            left = right - k + 1;
            sum+=nums[right];
            udmap[nums[right]]++;

            if(left<0){
                continue;
            }

            if(udmap.size()>=m){
                _maxSum = std::max(sum,_maxSum);
            }

            sum -= nums[left];
            if(--udmap[nums[left]] <= 0){
                udmap.erase(nums[left]);
            }
        }
        return _maxSum;
    }
};