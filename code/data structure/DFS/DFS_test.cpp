#include <iostream>
#include <vector>
using namespace std;

struct TreeNode
{
    int data;//节点数据
    TreeNode* left;
    TreeNode* right;

    TreeNode(int _data)
        : data(_data)
        ,left(nullptr)
        ,right(nullptr)
        {}//构造函数初始化
};


int dfs(TreeNode* root,vector<int>& current,vector<int>& longest)
{
    /*如果结点为空，则返回0*/
    if(!root) return 0;

    vector<int> leftLong;//左子树最长
    vector<int> rightLong;//右子树最长

    /*递归*/
    int leftdepth = dfs(root->left,leftLong,longest);
    int rightdepth = dfs(root->right,rightLong,longest);

    int currentdepth = leftdepth + rightdepth + 1;

    /*判断是否要更新*/
    if(currentdepth > longest.size())
    {
        longest.clear();
        longest.insert(longest.end(),leftLong.begin(),leftLong.end());
        longest.push_back(root->data);
        longest.insert(longest.end(),rightLong.rbegin(),rightLong.rend());
    }

    /*给current赋值*/
    if(leftdepth > rightdepth)
    {
        leftLong.push_back(root->data);
        current = leftLong;
        return leftdepth + 1;
    }
    else
    {
        rightLong.push_back(root->data);
        current = rightLong;
        return rightdepth + 1;
    }
}


int main()
{
    /*创建二叉树*/
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->right = new TreeNode(6);
    root->left->left->left = new TreeNode(7);

    vector<int> current;
    vector<int> longest;
    dfs(root,current,longest);

    cout << "最长路径长度为：" << longest.size() << endl;
    for(auto e: longest)
    {
        cout << e << ' ';
    }

    // 释放内存
    delete root->left->left->left;
    delete root->left->left;
    delete root->left->right;
    delete root->right->right;
    delete root->left;
    delete root->right;
    delete root;

    return 0;
}