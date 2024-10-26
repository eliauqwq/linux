#include <iostream>

using namespace std;

enum Color
{
    red,black
};


template <class K, class T>
struct RBTreeNode
{
    RBTreeNode<K,T>* _parent; // 父结点
    RBTreeNode<K,T>* _left;   // 左子结点
    RBTreeNode<K,T>* _right;  // 右子结点
    Color _color;//结点颜色
    pair<K, T> data;//存储的pair

    /*构造函数初始化*/
    RBTreeNode<K, T>(pair<K, T> wpair,Color wcolor)
        :data(wpair)
        ,_color(wcolor)
        ,_parent(nullptr)
        ,_left(nullptr)
        ,_right(nullptr)
        {}
};
