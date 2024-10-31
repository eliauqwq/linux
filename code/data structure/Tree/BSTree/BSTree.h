#pragma once
#include <iostream>
using namespace std;
/*
搜索二叉树顾名思义是利于搜索给定值的一种数据结构，他基本满足：
要么搜索二叉树为空，要么对于其根以及子树的根，都有左子树的数据一定小于这个根，右子树的数据一定大于这个根
*/

//使用模板定义搜索二叉树的节点
template<class K>
struct BSTreeNode
{
	BSTreeNode<K>* left;
	BSTreeNode<K>* right;
	K data;

	BSTreeNode(const K& k)
		:left(nullptr),
		right(nullptr),
		data(k){}
};

//二叉树定义
template<class K>
class BSTree
{
public:
	typedef  BSTreeNode<K> Node;
	void Insert(const K&  k);
	void Pop(const K& k);
	 ~BSTree();
	void InOrder()
	{
		_InOrder(this->root);
	}
private:
	Node* root = nullptr;

	void _InOrder(Node* _root)
	{
		if (_root == nullptr)
		{
			return;
		}

		_InOrder(_root->left);
		cout << _root->data << ' ';
		_InOrder(_root->right);
	}
};

//搜索二叉树的插入

template<class K>
void BSTree<K>:: Insert(const K& k)
{
	//首先判断一下二叉树的根节点是不是空
	if (this->root == nullptr)
	{
		root = new Node(k);
		return;
	}

	/*找到插入的位置*/
	Node* prev = nullptr;//保存插入位置的父节点
	Node* cur = this->root;//要插入的节点，从根开始

	while (cur != nullptr)
	{
		if (k < cur->data)//如果比当前位置的值小，则向左滑
		{
			prev = cur;
			cur = cur->left;
		}
		else if (k > cur->data)//如果比当前位置大，则向右滑
		{
			prev = cur;
			cur = cur->right;
		}
		else if(k==cur->data)//如果恰巧等于当前位置，则暂停并报错
		{
			cout << "插入元素有重复" << endl;
			return;
		}
	}
	/*找到合适的位置，开始插入*/
	cur = new Node(k);
	if (cur->data > prev->data)
	{
		prev->right = cur;
	}
	else
	{
		prev->left = cur;
	}
}

//搜索二叉树的删除
template<class K>
void BSTree<K>::Pop(const K& k)
{
	/*首先利用搜索二叉树特点寻找目标结点*/
	Node* cur = root;
	Node* father = nullptr;
	while (cur != nullptr)
	{
		if (cur->data > k)//大于目标值去找左数
		{
			father = cur;
			cur = cur->left;
		}
		else if (cur->data < k)//小于目标值去找右数
		{
			father = cur;
			cur = cur->right;
		}
		else/*正好找到，判断目标节点有几个孩子*/
		{
			if (cur->left == nullptr)//没有左孩子
			{
				/*判断目标节点是父节点的哪个孩子*/
				if (cur == father->left)
				{
					father->left = cur->right;//父亲接管其子结点
				}
				else if (cur == father->right)
				{
					father->right = cur->right;
				}
				delete cur;
				cur = nullptr;
				return;
			}
			else if (cur->right == nullptr)//没有右孩子
			{
				if (cur == father->left)
				{
					father->left = cur->left;
				}
				else if (cur == father->right)
				{
					father->right = cur->left;
				}
				delete cur;
				cur = nullptr;
				return;
			}
			else//左右孩子都有，则找到其右子树的最小结点与之交换之后再删除（或者左子树的最大结点）
			{
				Node* MinPar = cur;
				Node* Min = MinPar->right;
				while (Min->left != nullptr)
				{
					MinPar = Min;
					Min = Min->left;
				}
				swap(cur->data, Min->data);

				/*交换之后考虑Min是否还有右子树，如果有就交给其父亲接管*/
				if (Min == MinPar->right)
				{
					MinPar->right = Min->right;
				}
				else
				{
					MinPar->left = Min->right;
				}
				delete Min;
				Min = nullptr;
				return;
			}


		}
	}

}
template<class K>
void Destroy(BSTreeNode<K>* cur)
{
	if (cur->left != nullptr)
	{
		Destroy(cur->left);
	}
	if (cur->right != nullptr)
	{
		Destroy(cur->right);
	}

	delete cur;
	cur = nullptr;
}

//二叉树的销毁
template<class K>
 BSTree<K>::~BSTree()
{
	 Destroy(this->root);
}