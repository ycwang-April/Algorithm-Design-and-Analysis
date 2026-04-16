#include <iostream>
#include <string>
using namespace std;

struct RBNode {
    int key;
    string color;
    RBNode* lchild;
    RBNode* rchild;
    RBNode* parent;

    RBNode(int k)
        : key(k), color("red"), lchild(nullptr), rchild(nullptr), parent(nullptr) {
    }
};

// 普通 BST 插入：
// 1. 把新结点挂到树上
// 2. 返回“新插入的那个结点”
RBNode* BST_Insert(int k, RBNode*& root)
{
    RBNode* z = new RBNode(k);
    RBNode* parent = nullptr;
    RBNode* cur = root;

    while (cur != nullptr)
    {
        parent = cur;
        if (k < cur->key)
            cur = cur->lchild;
        else
            cur = cur->rchild;
    }

    z->parent = parent;

    if (parent == nullptr)
        root = z;
    else if (k < parent->key)
        parent->lchild = z;
    else
        parent->rchild = z;

    return z;
}

// 左旋
void LeftRotate(RBNode*& root, RBNode* x)
{
    RBNode* y = x->rchild;
    if (y == nullptr) return;

    x->rchild = y->lchild;
    if (y->lchild != nullptr)
        y->lchild->parent = x;

    y->parent = x->parent;

    if (x->parent == nullptr)
        root = y;
    else if (x == x->parent->lchild)
        x->parent->lchild = y;
    else
        x->parent->rchild = y;

    y->lchild = x;
    x->parent = y;
}

// 右旋
void RightRotate(RBNode*& root, RBNode* y)
{
    RBNode* x = y->lchild;
    if (x == nullptr) return;

    y->lchild = x->rchild;
    if (x->rchild != nullptr)
        x->rchild->parent = y;

    x->parent = y->parent;

    if (y->parent == nullptr)
        root = x;
    else if (y == y->parent->lchild)
        y->parent->lchild = x;
    else
        y->parent->rchild = x;

    x->rchild = y;
    y->parent = x;
}

// 红黑树插入
void RB_Insert(int k, RBNode*& root)
{
    RBNode* node = BST_Insert(k, root);
    node->color = "red";

    while (node != root && node->parent != nullptr && node->parent->color == "red")
    {
        RBNode* parent = node->parent;
        RBNode* grand = parent->parent;

        if (grand == nullptr) break;

        // 父亲是祖父左孩子
        if (parent == grand->lchild)
        {
            RBNode* uncle = grand->rchild;

            // Case 1：叔叔是红
            if (uncle != nullptr && uncle->color == "red")
            {
                parent->color = "black";
                uncle->color = "black";
                grand->color = "red";
                node = grand;   // 冲突上移
            }
            else
            {
                // Case 2：node 是右孩子
                if (node == parent->rchild)
                {
                    node = parent;
                    LeftRotate(root, node);
                    parent = node->parent;
                    grand = parent->parent;
                }

                // Case 3：node 是左孩子
                parent->color = "black";
                grand->color = "red";
                RightRotate(root, grand);
            }
        }
        // 父亲是祖父右孩子：对称情况
        else
        {
            RBNode* uncle = grand->lchild;

            // Case 1
            if (uncle != nullptr && uncle->color == "red")
            {
                parent->color = "black";
                uncle->color = "black";
                grand->color = "red";
                node = grand;
            }
            else
            {
                // Case 2：node 是左孩子
                if (node == parent->lchild)
                {
                    node = parent;
                    RightRotate(root, node);
                    parent = node->parent;
                    grand = parent->parent;
                }

                // Case 3：node 是右孩子
                parent->color = "black";
                grand->color = "red";
                LeftRotate(root, grand);
            }
        }
    }

    if (root != nullptr)
        root->color = "black";
}

// 中序遍历
void InOrder(RBNode* root)
{
    if (root == nullptr) return;
    InOrder(root->lchild);
    cout << root->key << "(" << root->color << ") ";
    InOrder(root->rchild);
}

// 简单测试
int main()
{
    RBNode* root = nullptr;

    RB_Insert(10, root);
    RB_Insert(20, root);
    RB_Insert(30, root);
    RB_Insert(15, root);
    RB_Insert(5, root);
    RB_Insert(1, root);
    RB_Insert(8, root);

    InOrder(root);
    cout << endl;

    return 0;
}