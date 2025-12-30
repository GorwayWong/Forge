package easy;

import java.util.ArrayDeque;
import java.util.Deque;

public class FindTargetBinarySearchTree {
    public TreeNode getNextLeftNode(Deque<TreeNode> leftDeque,TreeNode root){
        leftDeque.pollLast();
        TreeNode node = root.right;
        while(node!=null){
            leftDeque.addLast(node);
            node = node.left;
        }
        return leftDeque.peekLast();
    }
    public TreeNode getNextRightNode(Deque<TreeNode> rightDeque,TreeNode root){
        rightDeque.pollLast();
        TreeNode node = root.left;
        while(node!=null){
            rightDeque.addLast(node);
            node = node.right;
        }
        return rightDeque.peekLast();
    }
    public boolean findTarget(TreeNode root, int k) {
        if(root==null) return false;
        Deque<TreeNode> leftDeque = new ArrayDeque<>();
        Deque<TreeNode> rightDeque = new ArrayDeque<>();
        TreeNode node = new TreeNode();
        node = root;
        while(node!=null) {
            leftDeque.addLast(node);
            node = node.left;
        }
        node = root;
        while (node!=null) {
            rightDeque.addLast(node);
            node = node.right;
        }
        int sum = 0;
        TreeNode leftNode = leftDeque.peekLast();
        TreeNode rightNode = rightDeque.peekLast();
        while(leftNode.val<rightNode.val) {
            sum = leftNode.val+ rightNode.val;
            if (sum== k){
                return true;
            }else if(sum<k){
                leftNode = getNextLeftNode(leftDeque, leftNode);
            }else{
                rightNode = getNextRightNode(rightDeque, rightNode);
            }
        }
        return false;
    }
}
