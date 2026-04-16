#include <iostream>
#include <string>
using namespace std;;

struct RBNode {   // struct默认public
	int key;
	string color;
	RBNode* lchild;
	RBNode* rchild;
	RBNode* parent;

	RBNode(int k):key(k),color("red"),lchild(nullptr),rchild(nullptr),parent(nullptr) {}
};

RBNode* BST_Insert(int k, RBNode*& node,RBNode* parent = nullptr)
{
	if (node == nullptr)
	{
		node = new RBNode(k);
		node->parent = parent;
		return node;
	}
	if (k < node->key)
		return BST_Insert(k, node->lchild,node);
	else
		return BST_Insert(k, node->rchild,node);
}

void RB_Insert(int k,RBNode*& root)
{
	RBNode* node = BST_Insert(k, root);
	node->color = "red";


	while (node != root && node->parent && node->parent->color == "red")
	{
		RBNode* grand = node->parent->parent;
		if (node->parent == grand->lchild) // 父节点是祖父节点的左孩子
		{
			RBNode* uncle = grand->rchild;
			if (uncle != nullptr && uncle->color == "red")    // case1
			{
				uncle->color = "black";
				node->parent->color = "black";
				grand->color = "red";
				node = grand;
			}
			else  // uncle = nullptr 时要按黑色处理
			{
				if (node == node->parent->rchild) //case2
				{
					RBNode* tmp_parent = node->parent;
					grand->lchild = node;
					node->parent = grand;
					tmp_parent->rchild = node->lchild;
					node->lchild->parent = tmp_parent;
					node->lchild = tmp_parent;
					tmp_parent->parent = node;
					node = tmp_parent;
					// case2 做完进入 case3									
					RBNode* tmp_parent = node->parent;
					grand->lchild = tmp_parent->rchild;
					tmp_parent->rchild->parent = grand;
					tmp_parent->rchild = grand;
					grand->parent = tmp_parent;
					tmp_parent->color = "black";
					grand->color = "red";
				}
				else
				{
					RBNode* tmp_parent = node->parent;
					grand->lchild = tmp_parent->rchild;
					tmp_parent->rchild->parent = grand;
					tmp_parent->rchild = grand;
					grand->parent = tmp_parent;
					tmp_parent->color = "black";
					grand->color = "red";
				}
			}
		}
		else if (node->parent == grand->rchild) // 父节点是祖父节点的右孩子
		{
			RBNode* uncle = grand->lchild;
			if (uncle->color == "red")    // case1
			{
				uncle->color = "black";
				node->parent->color = "black";
				grand->color = "red";
				node = grand;
			}
			else
			{
				if (node == node->parent->lchild) //case2
				{
					RBNode* tmp_parent = node->parent;
					grand->rchild = node;
					node->parent = grand;
					tmp_parent->lchild = node->rchild;
					node->rchild->parent = tmp_parent;
					node->rchild = tmp_parent;
					tmp_parent->parent = node;
					node = tmp_parent;
					// case2 做完进入 case3									
					RBNode* tmp_parent = node->parent;
					grand->rchild = tmp_parent->lchild;
					tmp_parent->lchild->parent = grand;
					tmp_parent->lchild = grand;
					grand->parent = tmp_parent;
					tmp_parent->color = "black";
					grand->color = "red";
				}
				else
				{
					RBNode* tmp_parent = node->parent;
					grand->rchild = tmp_parent->lchild;
					tmp_parent->lchild->parent = grand;
					tmp_parent->lchild = grand;
					grand->parent = tmp_parent;
					tmp_parent->color = "black";
					grand->color = "red";
				}
			}
		}
	}
	root->color = "black";
}