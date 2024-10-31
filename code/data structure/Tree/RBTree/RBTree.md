# >>>>>>数据结构之红黑树

在之前的学习当中，我们了解到了一种利于排序和查找的数据结构——**搜索二叉树**。但单纯的搜索二叉树存在样本本身如果过于有序那么就容易退化成链表的这一问题，因此我们继续深入学习了AVL——平衡搜索二叉树。这种结构强调完全的平衡，但在大多数情况下，我们不需要结构过于平衡。而今天了解到的红黑树就是这种近似平衡的结构

## 红黑树的原理及特点
在红黑树中，某个结点到叶子节点的最长路径不会超过最短路径的两倍，这相较于AVL树的完全平衡所需要的代价更低，更好实现。在同样的样本情况下AVL的旋转次数往往远大于红黑树，对于我们的计算机而言，总体下来还是红黑树的性能更加的优越

**红黑树的特点**：

1. 结点不是黑色就是红色
2. 根节点一定是黑色的
3. 每个叶子结点(空结点)都是黑色
4. 任何红色节点的子结点一定是黑色(即不存在两个相连的红结点)
5. 任意结点到叶子节点的路径上的黑节点个数相同(黑高相同)

需要注意的是，在红黑树的结构中，我们把那些叶子节点之下的NULL结点称为叶子节点，并默认他们是黑色的。

我们简单分析以下4、5两条规则可知，*最短路径和最长路径中的黑结点个数相同，且不存在连续的红色节点*，那么最长路径就一定不会超过最短路径的两倍，最坏的情况就是最短节点都是黑节点，而最长路径是红黑结点交替的形式。

## 代码实现红黑树

### 一、结点以及红黑树的设计

STL中的map和set都是基于红黑树实现的，为了更好的理解map和set，我们这次采用模板的方式设计红黑树的结点，使其具有更好的可修改性和泛用性。

```
#include <iostream>

using namespace std;

enum Color
{
    red,black
};


template <class K>
struct Node
{
    Node<K>* _parent; // 父结点
    Node<K>* _left;   // 左子结点
    Node<K>* _right;  // 右子结点
    Color _color;//结点颜色
    K _data;//存储的K

    /*构造函数初始化*/
    Node<K>(K data,Color wcolor)
        :_data(data)
        ,_color(wcolor)
        ,_parent(nullptr)
        ,_left(nullptr)
        ,_right(nullptr)
        {}
};
```

### 二、插入的情况分析
首先我们要了解什么情况下才需要对整个树进行调整。我们默认所有的新插入结点均为红色，保证插入新节点之后两边黑高不变，但这有可能会违背红结点不相连的原则，因而我们需要对情况进行分类讨论。

1. 当叔叔结点是红色，如下图
```
       G(B)
      /    \
    P(R)   U(R)
    /
   N(R)
```
**注意，N不一定是新插入的结点，也可能是经过调整后返回的新子树根节点**

在这种情况下，我们可以通过简单的换色处理解决，即将P、U两节点换成黑色，将G换成红色，但是要向上递归，避免G的父结点也是红色着一种情况，直到递归到根节点

2. 叔叔节点是黑色或者不存在，且新插入的是左左/右右情况
```
       G(B)
      /    \
   P(R)     U(B)
   /
  N(R)
```
这种情况下我们要将P染成黑色，为了保证平衡，以G为轴，右旋P称为根节点，同时为了保平衡，将G染成红色
```
       P(B)
      /    \
   N(R)     G(R)
             \
              U(B)
```

3. 叔叔结点是黑色或不存在且左右、右左失衡
```
       G(B)
      /    \
   P(R)     U(B)
     \
      N(R)  <- 新插入节点
```
这种情况将P左旋，换成如下结构再以情况二讨论
```
       G(B)
      /    \
   N(R)     U(B)
   /
  P(R)
```

**需要注意的是，后面两种情况返回的不是红色节点，不会对上层结构造成影响，因此不需要递归检查**

### 三、左右旋的实现
在红黑树这种结构中，由于我们会涉及到很多指针修改，对于不同的复杂情况，需要考虑祖父、父、叔叔、等多层结构，为了更好的维护代码，我们选择采用迭代而非递归的方式进行插入，因此我们原先在AVL树中的左右旋函数就不太适合直接套用了，现在需要一个适合迭代结构的左右旋函数适配我们红黑树的插入。

**新的右旋函数**
```
 //右旋
    void RorateR(Node<K>* node)
    {
        Node<K>* node_son = node->left;//找到左孩子
        node->left = node_son->right;//领养左孩子的右子结点

        if(node_son->right != nullptr)//判断左孩子的右子结点是非为空，不是则传node给它作新父结点
            node_son->right->parent = node;

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
```

**新的左旋函数**
```
   //左旋
    void RorateL(Node<K>* node)
    {
        Node<K>* node_son = node->right;
        node->right = node_son->left;

        if(node_son->left != nullptr)
            node_son->left->parent = node;
        
        node_son->parent = node->parent;
        if(node->parent == nullptr)
            this->root = node_son;
        else if(node = node->parent->left)
            node->parent->left = node_son;
        else if(node = node->parent->right)
            node->parent->right = node_son;

        node_son->left = node;
        node->parent = node_son;
    }
```

### 四、插入修复
我们使用迭代的方式来进行插入后的平衡修复。首先我们要确定什么情况下需要循环，那就是当需平衡结点的父结点不为空并且为红色时，我们就需要对树进行平衡调整了。

搞清楚这个先驱条件之后我们再对情况进一步分析：

**如果调整节点在其祖父结点的左子树**

根据第二步我们粗略地分析，可以得出有如下的情况

1. 叔叔结点存在且为红色 这个时候不管调整节点是其父结点的那个节点，我们将父亲和叔叔染黑之后不会破坏红黑树的规则。因此可以直接染色处理

2. 叔叔结点不存在或者为黑色 这个时候考虑调整结点是否和父结点在同一边，也就是说是否同为其父结点的左/右结点，如果不是我们旋转调整成在同一边处理。当处于同一边时，我们要将父结点染黑，为了保证黑高一致，对祖父结点染红然后右旋，这样就能保证调整后左右黑高一致

**如果调整节点在其祖父节点的右子树**

跟上面的情况大差不差，我们根据镜像原理解决即可

代码实现如下：
```
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
```







    