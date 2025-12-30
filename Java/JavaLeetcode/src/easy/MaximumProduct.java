package easy;

import java.util.Arrays;

public class MaximumProduct {
    public int maximumProduct(int[] nums) {
        int res = 0;
        Arrays.sort(nums);
        int headMax=nums[nums.length-1]*nums[nums.length-2]*nums[nums.length-3];
        int tailMax=nums[0]*nums[1]*nums[2];
        int headTailMax = nums[0]*nums[1]*nums[nums.length-1];
        res = Math.max(headMax, tailMax);
        res = Math.max(res, headTailMax);
        return res;
    }
}
