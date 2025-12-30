package easy;

import java.util.*;

class  AverageOfLevels{
    public List<Double> averageOfLevels(TreeNode root) {
        List<Double> result = new ArrayList<>();
        Queue<TreeNode> queue = new LinkedList<>();
        if (root == null) return result;
        queue.add(root);
        double sum;
        while (!queue.isEmpty()) {
            sum = 0;
            int size = queue.size();
            for (int i = 0; i < size; i++) {
                if (queue.peek() != null && queue.peek().left != null) queue.add(queue.peek().left);
                if (queue.peek() != null && queue.peek().right != null) queue.add(queue.peek().right);
                sum += Objects.requireNonNull(queue.poll()).val;
            }
            result.add(sum /size);
        }
        return result;
    }
}