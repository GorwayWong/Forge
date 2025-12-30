package easy;

import java.util.HashMap;

public class _680ValidPalindrome {
    /**
     * 利用左右指针，每次判断中间的串是否是回文字符串
     */
    public boolean isPalindrome(String s) {
        if (s == null || s.length()<=1) return true;
        int left = 0, right = s.length()-1;
        while (left < right) {
            if (s.charAt(left) != s.charAt(right)) {
                return false;
            }
            left++;
            right--;
        }
        return true;
    }
    public boolean validPalindrome(String s) {
        if (s == null || s.length()<=1) return true;
        int i = 0, j = s.length() - 1;
        StringBuilder sb = new StringBuilder(s);
        int length = s.length();
        if(isPalindrome(s)) return true;
        while (i < j) {
            if(sb.charAt(i) != sb.charAt(j)){
                if(isPalindrome(sb.substring(0,i)+sb.substring(i+1,length))) return true;//substring左开右闭
                if(isPalindrome(sb.substring(0,j)+sb.substring(j+1,length))) return true;
                return false;//第一次判断没有回文的时候就能返回，不然会超时
            }
            i++;
            j--;
        }
        return false;
    }
}
