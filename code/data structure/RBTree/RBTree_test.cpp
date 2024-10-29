#include <iostream>

using namespace std;

enum Color
{
    red,black
};


template <class K>
struct Node
{
    Node<K>* parent; // 父结点
    Node<K>* left;   // 左子结点
    Node<K>* right;  // 右子结点
    Color _color;//结点颜色
    K _data;//存储的K

    /*构造函数初始化*/
    Node<K>(K data,Color wcolor)
        :_data(data)
        ,_color(wcolor)
        ,parent(nullptr)
        ,left(nullptr)
        ,right(nullptr)
        {}
};

template<class K>
class RBtree
{
public:

    RBtree<K>()
    :root(nullptr)
    {}

    ~RBtree()
    {
        Del(this->root);
    }

    void Del(Node<K>* _root)
    {
        if(_root == nullptr)
        {
            return ;
        }

        Del(_root->left);
        Del(_root->right);
        delete _root;
    }

    void Insert(K data)
    {
        insert(data);
    }

    void Inorder()
    {
        inorder(root);
        cout << endl;
    }

    void _te()
    {
        Getroot();
    }

private:

    Node<K>* root;

    void inorder(Node<K>* _root)
    {
        if(_root == nullptr)
            return ;

        inorder(_root->left);
        cout << _root->_data <<((_root->_color == black)? "black":"red") << ' ';
        inorder(_root->right);
    }

    //右旋
    void RorateR(Node<K>* node)
    {
        Node<K>* node_son = node->left;//找到左孩子
        node->left = node_son->right;//领养左孩子的右子结点

        if(node_son->right != nullptr)//判断左孩子的右子结点是非为空，不是则传node给它作新父结点
        {
            node_son->right->parent = node;
        }
        node_son->parent = node->parent;
        if(node->parent==nullptr)//node是根节点
            this->root=node_son;//更新树的根
        else if(node == node->parent->left)//node是其父结点的左子节点
            node->parent->left = node_son;
        else if(node == node->parent->right)//node是其父结点的右子结点
            node->parent->right = node_son;
        
        node_son->right = node;
        node->parent = node_son;
    }

    //左旋
    void RorateL(Node<K>* node)
    {
        Node<K>* node_son = node->right;
        node->right = node_son->left;

        if(node_son->left != nullptr)
        {
            node_son->left->parent = node;
        }
        node_son->parent = node->parent;
        if(node->parent == nullptr)
            this->root = node_son;
        else if(node == node->parent->left)
            node->parent->left = node_son;
        else if(node == node->parent->right)
            node->parent->right = node_son;

        node_son->left = node;
        node->parent = node_son;
    }

    //插入修复函数
    void InsertFix(Node<K>* node)
    {
        while(node != root&&node->parent->_color == red)
        {
            //插入位置发生在祖父结点的左子树
            if(node->parent == node->parent->left)
            {
                Node<K>* uncle = node->parent->parent->right;
                
                if(uncle && uncle->_color == red)
                {
                   
                    node->parent->_color = black;
                    uncle->_color = black;//父亲叔叔变黑色
                    node->parent->parent->_color = red;//祖父变称红色
                    node = node->parent->parent ;//向上迭代，考虑祖父
                }
                else
                {
                    if(node == node->parent->right)
                    {
                        node = node->parent;
                        RorateL(node);
                    }

                    
                        node->parent->parent->_color = red;//祖父染红
                        node->parent->_color = black;//父亲染黑
                        RorateR(node->parent->parent);//右旋祖父
                }
                  
            }  
            else//插入位置在祖父结点右子树
            {
                Node<K>* uncle = node->parent->parent->left;//叔叔
                if(uncle && uncle->_color == red)
                {

                    node->parent->_color = black;
                    uncle->_color = black;
                    node->parent->parent->_color = red;
                    node = node->parent->parent;

                }
                else
                {
                    if(node == node->parent->left)//情况二：右左叔叔为黑
                    {
                        node = node->parent;
                        RorateR(node);
                    }
                    
                        node->parent->parent->_color = red;
                        node->parent->_color = black;
                        RorateL(node->parent->parent);
                }  
            }
        }
        root->_color = black;//根节点始终为黑
    }

    /*插入*/
    void insert(K data)
    {
        /*根节点是空的*/
        if(this->root == nullptr)
        {
            this->root = new Node<K>(data,black);
            return;
        }

        /*根节点不为空*/
        Node<K>* _parent = this->root;
        Node<K>* cur = _parent;
        while(cur != nullptr)
        {
            if(data > cur->_data)
            {
                _parent = cur;
                cur = cur->right;
            }
            else if( data < cur->_data)
            {
                _parent = cur;
                cur = cur->left;
            }
            else
                return ;//不允许插入重复
        }

        /*判断大小*/
        if(data < _parent->_data)
        {
            Node<K>* node = new Node<K>(data,red);//保证新插入的一定是红色
            _parent->left = node;
            node->parent = _parent;
            InsertFix(node);
        }
        else if( data > _parent->_data)
        {
            Node<K>* node = new Node<K>(data,red);//保证新插入的一定是红色
            _parent->right = node;
            node->parent = _parent;
            InsertFix(node);
        }
    }

    void Getroot()
    {
        cout<<root->_data<<' ';
    }
    
};


int main()
{
    RBtree<int> tree;
    tree.Insert(2);
    tree.Insert(3);
    tree.Insert(6);
    tree.Insert(5);
    tree.Insert(4);
    tree.Insert(2);
    tree.Insert(9);
    tree.Insert(11);
    tree.Insert(8);

    tree._te();
    tree.Inorder();
}


