#include<vector>

class _566Solution {
public:
    std::vector<std::vector<int>> matrixReshape(std::vector<std::vector<int>>& nums, int r, int c) {
        int m = nums.size();
        int n = nums[0].size();
        if (m * n != r * c) {
            return nums;
        }
        // 二维vector的初始化方法
        std::vector<std::vector<int>> ans(r, std::vector<int>(c));
        // 先把原来的矩阵平铺再一个个填入新矩阵
        for (int x = 0; x < m * n; ++x) {
            ans[x / c][x % c] = nums[x / n][x % n];
        }
        return ans;
    }
};