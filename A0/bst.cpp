#include <iostream>
#include "bst.h"
#include "customErrorClass.h"

using namespace std;

treenode *makeatreenode(int val)
{
    treenode *box;
    box = new treenode;

    box->dat = val;
    box->lchild = NULL;
    box->rchild = NULL;
    return box;
}

BST::BST()
{
    root = NULL;
}

// public functions
void BST::in()
{
    if (root == NULL)
    {
        throw MyException("Tree is empty");
    }
    cout << "Inorder: ";
    inHelper(root);
    cout << endl;
}

void BST::pre()
{
    if (root == NULL)
    {
        throw MyException("Tree is empty");
    }
    cout << "Preorder: ";
    preHelper(root);
    cout << endl;
}

void BST::post()
{
    if (root == NULL)
    {
        throw MyException("Tree is empty");
    }
    cout << "Postorder: ";
    postHelper(root);
    cout << endl;
}

void BST::insert(int val)
{
    if (root == NULL)
    {
        root = makeatreenode(val);
    }
    else
    {
        insertHelper(root, val);
    }
}

void BST::remove(int val)
{
    if (root == NULL)
    {
        throw MyException("Tree is empty");
    }
    root = removeHelper(root, val);
}

bool BST::search(int val)
{
    if (root == NULL)
    {
        throw MyException("Tree is empty");
    }
    return searchHelper(root, val);
}

int BST::treeHeight()
{
    if (root == NULL)
    {
        throw MyException("Tree is empty");
    }
    return treeHeightHelper(root);
}

int BST::nodeHeight(int val)
{
    if (root == NULL)
    {
        throw MyException("Tree is empty");
    }
    return nodeHeightHelper(root, val);
}

bool BST::isBalanced()
{
    if (root == NULL)
    {
        throw MyException("Tree is empty");
    }
    return isBalancedHelper(root);
}

int BST::numNodes()
{
	return numNodesHelper(root);
}

bool BST::isWorstCaseSenario()
{
    return isWorstCaseSenarioHelper(root);
}

// private functions
void BST::inHelper(treenode *root)
{
    if (root == NULL)
    {
        return;
    }

    inHelper(root->lchild);
    cout << root->dat << " ";
    inHelper(root->rchild);
}

void BST::preHelper(treenode *root)
{
    if (root == NULL)
    {
        return;
    }

    cout << root->dat << " ";
    preHelper(root->lchild);
    preHelper(root->rchild);
}

void BST::postHelper(treenode *root)
{
    if (root == NULL)
    {
        return;
    }

    postHelper(root->lchild);
    postHelper(root->rchild);
    cout << root->dat << " ";
}

void BST::insertHelper(treenode *root, int val)
{
    if (root->dat == val)
    {
        return;
    }

    if (root->dat > val)
    {
        if (root->lchild == NULL)
        {
            root->lchild = makeatreenode(val);
        }
        else
        {
            insertHelper(root->lchild, val);
        }
    }
    else
    {
        if (root->rchild == NULL)
        {
            root->rchild = makeatreenode(val);
        }
        else
        {
            insertHelper(root->rchild, val);
        }
    }
}

treenode *BST::removeHelper(treenode *root, int val)
{
    if (root == NULL)
    {
        return root;
    }

    if (root->dat > val)
    {
        root->lchild = removeHelper(root->lchild, val);
    }
    else if (root->dat < val)
    {
        root->rchild = removeHelper(root->rchild, val);
    }
    else
    {
        // case 1: no childern
        if (root->lchild == NULL && root->rchild == NULL)
        {
            delete root;
            return NULL;
        }
        // case 2: right child
        else if (root->lchild == NULL)
        {
            treenode *tmp;
            tmp = root->rchild;
            delete root;
            return tmp;
        }
        // case 2: left child
        else if (root->rchild == NULL)
        {
            treenode *tmp;
            tmp = root->lchild;
            delete root;
            return tmp;
        }
        // case 3: two children
        else
        {
            treenode *tmp;
            tmp = root->rchild;
            while (tmp->lchild != NULL)
            {
                tmp = tmp->lchild;
            }

            root->dat = tmp->dat;
            root->rchild = removeHelper(root->rchild, tmp->dat);
        }
    }
    return root;
}

bool BST::searchHelper(treenode *root, int val)
{
    if (root == NULL)
    {
        return false;
    }

    if (root->dat == val)
    {
        return true;
    }

    if (root->dat > val)
    {
        return searchHelper(root->lchild, val);
    }
    else
    {
        return searchHelper(root->rchild, val);
    }
}

int BST::treeHeightHelper(treenode *root)
{
    if (root == NULL)
    {
        return -1;
    }

    int lheight, rheight;
    lheight = treeHeightHelper(root->lchild);
    rheight = treeHeightHelper(root->rchild);

    if (lheight > rheight)
    {
        return 1 + lheight;
    }
    else
    {
        return 1 + rheight;
    }
}

int BST::nodeHeightHelper(treenode *root, int val)
{
    if (root->dat == val)
    {
        return 0;
    }

    if (root->dat > val)
    {
        int h = nodeHeightHelper(root->lchild, val);
        if (h == -1)
        {
            return -1; // return -1 for a tree without the chosen node
        }
        else
        {
            return h + 1;
        }
    }
    else
    {
        int h = nodeHeightHelper(root->rchild, val);
        if (h == -1)
        {
            return -1; // return -1 for a tree without the chosen node
        }
        else
        {
            return h + 1;
        }
    }
}

bool BST::isBalancedHelper(treenode *root)
{
    if (root == NULL)
    {
        return true;
    }

    int lheight, rheight;
    lheight = treeHeightHelper(root->lchild);
    rheight = treeHeightHelper(root->rchild);

    if (abs(lheight - rheight) <= 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int BST::numNodesHelper(treenode *root)
{
	if (root == NULL)
	{
		return 0;
	}

	int lcount, rcount;
	lcount = numNodesHelper(root->lchild);
	rcount = numNodesHelper(root->rchild);

	return 1 + lcount + rcount;
}

bool BST::isWorstCaseSenarioHelper(treenode *root)
{
    int numberOfNodes = numNodesHelper(root);
    int treeHeight = treeHeightHelper(root);

    return numberOfNodes - 1 == treeHeight;
}
