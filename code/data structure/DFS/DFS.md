# >>>>>>>>二叉树中的深度优先算法(DFS)
    :smile 我们知道二叉树中的**路径**是指从某个结点到另外一个结点的结点数。在某些场景中我们需要利用算法找到二叉树中
的最长路径，在这种情况下DFS算法可以很快地帮助我们解决这个问题。

# 一、什么是DFS算法
>   DFS，也就是深度优先算法，故名思意，就是以深度为优先考虑的算法，尽量在某一条路径上走的更深，避免回溯，尽可能找到
>一条最长的路径。

# 二、DFS算法的整体思路
    为了更直观地了解DFS算法的过程，我们利用图解来更好地理解DFS算法。
    例如，现在我们给定一个二叉树如下：

       1
      / \
     2   3
    / \
   4   5

   DFS的过程：

   1.输入树的根“1”，“1”有两个子结点：“2”、“3”，我们默认优先计算左子树的深度

   2.访问结点“2”
    有两个子结点，先访问左边结点“4”

   3.访问结点“4”
    “4”没有子结点，我们返回(1,[4]);

   4.访问结点“5”
    “5”没有子结点，我们返回(1,[5]);

   5.回到结点“2”
    “2”的子节点已经访问完成，分别返回了(1,[4]),(1,[5]),此时的深度currentdpeth=1+1+1=3,
    我们返回(2,[4,2,5])。

   6.访问结点“3”
    “3”没有子结点，返回(1,[3])。

   7.回到结点“1”
    左边返回(2,[4,2,5]),右边返回(1,[3])。此时的深度=1+1+2=4>3，我们更新深度=4。
    同时更新[4,2,1,3].

# 三、具体的代码实现
    为了使代码更简洁，我们这里采用递归的写法。首先我们要确定dfs函数的参数个数以及各自的作用。我们需要一个TreeNode*的
来代表传入的根节点，一个vector<int> longest来代表已经记录到的最长路径，一个vector<int> current来记录子树的深度。

1.首先判断传入的root指针是否指向空，如果指向空那么我们就返回0代表这个子树深度为0。
```
 /*如果结点为空，则返回0*/
    if(!root) return 0;
```

2.递归记录左右子树的深度，并传入leftLong和rightLong来记录子树中的最深的路径
```
    vector<int> leftLong;//左子树最长
    vector<int> rightLong;//右子树最长

    /*递归*/
    int leftdepth = dfs(root->left,leftLong,longest);
    int rightdepth = dfs(root->right,rightLong,longest);
```
3.计算此时路径的长度并与longest作比较，如果后者更短那么我们更新longest
```
    int currentdepth = leftdepth + rightdepth + 1;

    /*判断是否要更新*/
    if(currentdepth > longest.size())
    {
        longest.clear();
        longest.insert(longest.end(),leftLong.begin(),leftLong.end());
        longest.push_back(root->data);
        longest.insert(longest.end(),rightLong.rbegin(),rightLong.rend());
    }
```
>这里要注意的是右边最深路径传入longest时的顺序，由于在rightLong中是自下往上的，这里我们倒过来

4.更新current，判断左右最深路径谁更长
```
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
```

5.测试
```
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
```





