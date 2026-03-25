#include "LLRB.h"
#include "customErrorClass.h"

// ++++++++++++++++++++++++++++++ PUBLIC +++++++++++++++++++++++++++++++++++++++

LLRBTREE::LLRBTREE()
{
    TNULL = new Node(0);
    TNULL->color = BLACK;
    TNULL->left = TNULL;
    TNULL->right = TNULL;

    root = TNULL;
}

LLRBTREE::~LLRBTREE()
{
    deleteSubtree(root);
}

void LLRBTREE::insert(int data)
{
    insert(root, data);

    if (root != TNULL)
    {
        root->color = BLACK;
    }
}

void LLRBTREE::printTree()
{
    if(root == TNULL)
    {
        cout << "Tree is empty" << endl;
        return;
    }
    print(root, 0);
}

// ++++++++++++++++++++++++++++++ PRIVATE +++++++++++++++++++++++++++++++++++++++++++++

void LLRBTREE::leftRotate(Node*& node)
{
    // exeption handling
    if (node == nullptr || node == TNULL)
    {
        throw MyException("Cannot rotate a null node");
    }
    if (node->right == nullptr || node->right == TNULL)
    {
        throw MyException("Node has no right child to rotate");
    }

    // rotate node and update colors
    Node* x = node->right;
    node->right = x->left;
    x->left = node;
    x->color = node->color;
    node->color = RED;
    node = x;

    rotationCount++;
}

void LLRBTREE::rightRotate(Node*& node)
{
    // exeption handling
    if (node == nullptr || node == TNULL)
    {
        throw MyException("Cannot rotate a null node");
    }
    if (node->left == nullptr || node->left == TNULL)
    {
        throw MyException("Node has no left child to rotate");
    }

    // rotate node and update colors
    Node* x = node->left;
    node->left = x->right;
    x->right = node;
    x->color = node->color;
    node->color = RED;
    node = x;

    rotationCount++;
}

bool LLRBTREE::isRed(Node* node)
{
    if (node == nullptr || node == TNULL || node->color == BLACK)
    {
        return false;
    }
    return true;
}

void LLRBTREE::flipColor(Node* node)
{
    // exception handling
    if (node == nullptr || node == TNULL)
    {
        throw MyException("Cannot flip colors on a null node");
    }

    // flip parent
    if (node->color == RED)
    {
        node->color = BLACK;
    }
    else
    {
        node->color = RED;
    }

    // flip left child
    if (node->left != TNULL)
    {
        if (node->left->color == RED)
        {
            node->left->color = BLACK;
        }
        else
        {
            node->left->color = RED;
        }
    }

    // flip right child
    if (node->right != TNULL)
    {
        if (node->right->color == RED)
        {
            node->right->color = BLACK;
        }
        else
        {
            node->right->color = RED;
        }
    }
}

void LLRBTREE::insert(Node*& node, int data)
{
    if (node == TNULL)
    {
        node = new Node(data);
        node->left = TNULL;
        node->right = TNULL;
        return;
    }

    if (data < node->data)
    {
        insert(node->left, data);
    }
    else if (data > node->data)
    {
        insert(node->right, data);
    }

    if (isRed(node->right) && !isRed(node->left))
    {
        leftRotate(node);
    }

    if (isRed(node->left) && isRed(node->left->left))
    {
        rightRotate(node);
    }

    if (isRed(node->left) && isRed(node->right))
    {
        flipColor(node);
    }
}

void LLRBTREE::deleteSubtree(Node* node)
{
    if (node != TNULL)
    {
        deleteSubtree(node->left);
        deleteSubtree(node->right);
        delete node;
    }
}


void LLRBTREE::print(Node* root, int space )
{
    if (root == TNULL || root == nullptr)
    {
        return;
    }

    space += 10;
    print(root->right, space);

    cout << endl;
    for (int i = 10; i < space; i++)
    {
        cout << " ";
    }
        
    string color_code = (root->color == RED) ? RED_COLOR : BLACK_COLOR;
    cout << color_code << root->data << RESET_COLOR;
    cout << endl;
    print(root->left, space);
}
