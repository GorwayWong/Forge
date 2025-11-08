#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <vector>

class _2090Solution
{
public:
    std::vector<int> getAverages(std::vector<int> &nums, int k)
    {
        int n =nums.size();
        int left, right,mid;
        std::vector<int> res(n,-1);
        long long sum = 0;
        for(int i =0;i<nums.size();i++){
            right = i;
            left = i-2*k;
            sum+=nums[right];
            if((left+right)/2 < 0){
                continue;
            }else if(i<2*k){
                continue;
            }
            res[i-k]=sum/(2*k+1);
            //res.push_back(sum/(2*k+1));
            sum-=nums[left];
        }
        return res;
    }
};