package easy;

import java.util.HashMap;
import java.util.Map;

public class FindErrorNums {
    public int[] findErrorNums(int[] nums) {
        Map<Integer,Integer> map = new HashMap<Integer,Integer>();
        int [] result = new int[2];
        for(int num : nums){
            if(!map.containsKey(num)){
                map.put(num,1);
            }else{
                result[0] = num;
            }
        }
        for(int i=1;i<= nums.length;i++){
            if(!map.containsKey(i)){
                result[1]=i;
                break;
            }
        }
        return result;
    }
}
