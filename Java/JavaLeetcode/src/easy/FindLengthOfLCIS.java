package easy;

public class FindLengthOfLCIS{
    public int findLengthOfLCIS(int[] nums) {
        if(nums == null || nums.length == 0) return 0;
        int res = 0,count=0;
        int j;
        for(int i = 0; i < nums.length; i++){
            j=i;
            count=1;
            while(j+1<nums.length&&nums[j+1]>nums[j]){
                count++;
                j++;
            }
            res=Math.max(res,count);
            i=j;
        }
        return res;
    }
}
