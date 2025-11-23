#include <algorithm>
#include <cmath>

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class _543Solution
{
public:
    int DFS(TreeNode *root)
    {
        if (root == nullptr)
            return 0;
        if (root->left == nullptr && root->right == nullptr)
            return 1;
        if (root->left == nullptr)
            return DFS(root->right) + 1;
        if (root->right == nullptr)
            return DFS(root->left) + 1;
        return std::max(DFS(root->left) + 1, DFS(root->right) + 1);
    }
    int ans;
    void preOrder(TreeNode* root){
        if(root==nullptr) return;
        int temp = DFS(root->left)+DFS(root->right);
        if(temp>ans) ans=temp;
        preOrder(root->left);
        preOrder(root->right);
    }
    int diameterOfBinaryTree(TreeNode *root)
    {
        preOrder(root);
        return ans;
    }
};