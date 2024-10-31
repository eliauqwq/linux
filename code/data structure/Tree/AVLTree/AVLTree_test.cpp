#include <iostream>
using namespace std;

struct AVLTreeNode
{
    AVLTreeNode* left ; //左子结点指针
    AVLTreeNode* right ; //右子节点指针
    int key ;//储存数据
    int height;

    //构造函数
    AVLTreeNode(int K)
    :left(nullptr),
     right(nullptr),
     height(1),
     key(K){}
};

//获得某点高度
int height(AVLTreeNode* root)
{
    return root? root->height : 0 ;
}

//获得某点平衡因子
int GetBlance(AVLTreeNode* root)
{
    return root? height(root->left) - height(root->right) : 0 ;//左子树高度减右子树高度
}

//更新某点高度，利用递归思想
int updateheight(AVLTreeNode* root)
{
    return 1 + max(height(root->left),height(root->right));
}

//右旋
AVLTreeNode* rightRotate(AVLTreeNode* root)
{
    AVLTreeNode* son=root->left;//根节点左子结点(20)
    AVLTreeNode* son_r=son->right;//根节点左子结点的右子树(15)

    son->right=root;//旋转
    root->left=son_r;//领养

    //准备更新高度
    root->height = updateheight(root);
    son->height = updateheight(son);

    //返回新的根节点
    return son;
}

//左旋
AVLTreeNode* leftRotate(AVLTreeNode* root)
{
    AVLTreeNode* son = root->right;
    AVLTreeNode* son_l=son->left;

    son->left = root;
    root->right = son_l;

    root->height = updateheight(root);
    son->height = updateheight(son);
    return son ;
    
}


AVLTreeNode* insert(AVLTreeNode* root,int key)
{
    //1.和搜索二叉树一样，正常插入
    if(!root)
    {
        return new AVLTreeNode(key);
    }

    if(key < root->key)
    {
        root->left = insert(root->left,key);
    }else if(key > root->key)
    {
        root->right = insert(root->right,key);
    }
    else
    {
        return root;//不允许插入重复值
    }

    //2.更新新树结点的高度
    root->height = updateheight(root);

    //3.求新树结点的平衡因子
    int balance = GetBlance(root);

    //4.判断有没有失衡出现

    //左-左失衡，右旋转
    if(balance > 1&& key <root->left->key)
    {
        return rightRotate(root);
    }

    //右右失误，左旋转
    if(balance < -1&& key > root->right->key)
    {
        return leftRotate(root);
    }

    //左-右失衡
    if(balance > 1&& key > root->left->key )
    {
        //先左旋转
        root->left = leftRotate(root->left);

        return rightRotate(root);
    }

    //右-左失衡
    if(balance < -1&& key < root->right->key)
    {
        root->right = rightRotate(root->right);

        return leftRotate(root);
    }

    return root;//没失衡则正常返回
}

//找到最小的结点
AVLTreeNode* MinNode( AVLTreeNode* root)
{
    AVLTreeNode* node=root;
    while(node->left!=nullptr)
    {
        node = node->left;
    }
    return node;
}

//AVL删除操作
AVLTreeNode* Pop(AVLTreeNode* root,int key)
{
    if(root==NULL)
        return root;

    //1.正常删除
    if(key < root->key)
        root->left = Pop(root->left ,key);
    else if(key > root->key)
        root->right = Pop(root->right,key);
    else if( key == root-> key)
    {
        if(!root->left || !root->right)//只有一个子结点或者没有子节点
        {
            AVLTreeNode* temp = root->left ? root->left : root->right;
            //无孩子
            if(!temp)
            {
                temp=root;
                root=nullptr;
            }
            else//有一个子树
            {
                root->key=temp->key;
                root->left=temp->left;
                root->right=temp->right;
            }
            delete temp;
        }
        else
        {
            AVLTreeNode* temp = MinNode(root->right);
            root->key=temp->key;
            root->right=Pop(root->right,temp->key);
        }
    }

    if(!root)
        return root;

    //2.更新新树结点的高度
    root->height = updateheight(root);

    //3.求新树结点的平衡因子
    int balance = GetBlance(root);

    //4.判断有没有失衡出现

    //左-左失衡，右旋转
    if(balance > 1&& key < root->left->key)
    {
        return rightRotate(root);
    }

    //右右失误，左旋转
    if(balance < -1&& key > root->right->key)
    {
        return leftRotate(root);
    }

    //左-右失衡
    if(balance > 1&& key > root->left->key )
    {
        //先左旋转
        root->left = leftRotate(root->left);

        return rightRotate(root);
    }

    //右-左失衡
    if(balance < -1&& key < root->right->key)
    {
        root->right = rightRotate(root->right);

        return leftRotate(root);
    }

    return root;//没失衡则正常返回
}

//中根遍历
void Inorder(AVLTreeNode* root)
{
    if(root)
    {
    Inorder(root->left);
    cout << root->key << ' ';
    Inorder(root->right);
    }

}

void freeTree(AVLTreeNode* node) {
    if (node) {
        freeTree(node->left);
        freeTree(node->right);
        delete node;
    }
}

int main()
{
    AVLTreeNode* root=nullptr;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    Inorder(root);
    Pop(root,20);
    Pop(root,50);
    cout<<endl;
    Inorder(root);

    freeTree(root);

    return 0;
}