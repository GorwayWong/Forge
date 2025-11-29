#include<unordered_map>
#include<vector>

class _594Solution {
public:
    int findLHS(std::vector<int>& nums) {
        std::unordered_map<int, int> udmap;
        int length = nums.size();
        for (int i = 0; i < length; i++) {
            if (!udmap.count(nums[i])) {
                udmap.insert({nums[i], 1});
            } else {
                udmap[nums[i]]++;
            }
        }
        int ans = 0;
        int temp;
        for (auto pair : udmap) {
            if (udmap.count(pair.first + 1)) {
                temp = udmap[pair.first + 1] + pair.second;
                if (temp > ans)
                    ans = temp;
            }
        }
        return ans;
    }
};