#include "LLRB.h"

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

void LLRBTREE::insert(int key)
{
    Node* node = nullptr;
    node = new Node(key);

    node->left  = TNULL;
    node->right = TNULL;

    if (root == TNULL)
    {
        root = node;
        root->color = BLACK;
        return;
    }

    insertR(root, node);
    insertFix(node);
}

void LLRBTREE::remove(int key)
{
    removeR(root, key);
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

void LLRBTREE::leftRotate(Node* y)
{
    rotationCount++;

    Node* x = y->right;
    if (x == TNULL || x == nullptr)
    {
        return;  // Prevent invalid rotation
    }
    y->right = x->left;  // adoption

    if (x->left != TNULL) // updating parent of adopted left child
    {
        x->left->parent = y; 
    }

    // update parent of x
    x->parent = y->parent;
    if (y->parent == nullptr)
    {
        root = x;
    }
    else if (y == y->parent->left)
    {
        y->parent->left = x;
    }
    else
    {
        y->parent->right = x;
    }

    x->left = y;
    y->parent = x;
    
}

void LLRBTREE::rightRotate(Node* y)
{
    rotationCount++;

    Node* x = y->left;
    if (x == TNULL || x == nullptr)
    {
        return;  // Prevent invalid rotation
    }
    y->left = x->right;  // adoption

    if(x->right != TNULL) // updating parent of adopted left child
    {
        x->right->parent = y; 
    }

    // update parent of x
    x->parent = y->parent;
    if(y->parent == nullptr)
    {
        root = x;
    }
    else if(y == y->parent->left)
    {
        y->parent->left = x;
    }
    else
    {
        y->parent->right = x;
    }

    x->right = y;
    y->parent = x;
}

void LLRBTREE::insertR(Node*& root, Node*& node)
{
    if(root == TNULL)
    {
        root = node;
        return;
    }

    if(node->data < root->data)
    {
        if(root->left == TNULL)
        {
            root->left = node;
            node->parent = root;
        }
        else
        {
            insertR(root->left, node);
        }
    }
    else
    {
        if(root->right == TNULL)
        {
            root->right = node;
            node->parent = root;
        }
        else
        {
            insertR(root->right, node);
        }
    }
}

void LLRBTREE::insertFix(Node* k)
{
    Node* uncle;
    
    // property 3 violation - when parent is red
    while(k != root && k->parent->color == RED)
    {
        if (k->parent == k->parent->parent->right) // parent is right child
        {
            uncle = k->parent->parent->left;

            if (uncle->color == RED) // CASE 2 - Red Uncle
            {
                uncle->color = BLACK;
                k->parent->color = BLACK;
                k->parent->parent->color = RED;

                // update k to move up the tree
                k = k->parent->parent;
            }
            else // CASE 3 or 4 - Black Uncle
            {
                if (k == k->parent->left) // CASE 3 - Triangle case
                {
                    k = k->parent;
                    rightRotate(k);
                }

                // CASE 4
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                leftRotate(k->parent->parent);
            }
        }
        else if (k->parent == k->parent->parent->left) // parent is left child
        {
            uncle = k->parent->parent->right;

            if (uncle->color == RED) // CASE 2 - Red Uncle
            {
                uncle->color = BLACK;
                k->parent->color = BLACK;
                k->parent->parent->color = RED;

                // update k to move up the tree
                k = k->parent->parent;
            }
            else // CASE 3 or 4 - Black Uncle
            {
                if (k == k->parent->right) // CASE 3 - Triangle case
                {
                    k = k->parent;
                    leftRotate(k);
                }

                // CASE 4
                k->parent->color = BLACK;
                k->parent->parent->color = RED;
                rightRotate(k->parent->parent);
            }
        }

        if (k == root)
        {
            break;
        }
    }

    root->color = BLACK;
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
