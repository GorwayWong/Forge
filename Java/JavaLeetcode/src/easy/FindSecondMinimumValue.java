package easy;

public class FindSecondMinimumValue {
    public long firstMin = Long.MAX_VALUE;
    public long secondMin = Long.MAX_VALUE;
    public void preOrder(TreeNode root) {
        if(root == null) return;
        if(root.val< firstMin) { // 不要第一小值和第二小值相等，不加=号
            secondMin = firstMin;
            firstMin = root.val;
        }else if(root.val!=firstMin&&root.val < secondMin) {// 不要第一小值和第二小值相等，要严格大于第一小值的作为第二小值
            secondMin =root.val;
        }
        preOrder(root.left);
        preOrder(root.right);
    }
    public int findSecondMinimumValue(TreeNode root) {
        preOrder(root);
        return secondMin == Long.MAX_VALUE?-1:(int)secondMin;
    }
}
