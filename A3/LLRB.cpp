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


void LLRBTREE::removeR(Node*& node, int key)
{
    if (node == TNULL)
    {
        return;
    }

    if (key < node->data)
    {
        removeR(node->left, key);
    }
    else if (key > node->data)
    {
        removeR(node->right, key);
    }
    else // node to be deleted
    {
        Node* z = node; // node to delete
        Node* y = node; // successor if any
        Node* x;
        Color y_original_color = node->color;

        if (node->left == TNULL && node->right != TNULL) // case 1
        {
            x = node->right;
            transplant(node, node->right);
        }
        else if (node->left != TNULL && node->right == TNULL) // case 2
        {
            x = node->left;
            transplant(node, node->left);
        }
        else if (node->left == TNULL && node->right == TNULL)
        {
            x = TNULL;
            transplant(node, TNULL);
        }
        else // case 3
        {
            y = successor(y->right);
            y_original_color = y->color;
            x = y->right; // to avoid orphans

            if (y->parent != node)
            {
                transplant(y, y->right);

                y->right = node->right;
                y->right->parent = y;
            }
            y->left = node->left;
            y->left->parent = y;

            transplant(node, y);
            y->color = node->color;
        }

        if (y_original_color == BLACK)
        {
            deleteFix(x);
        }
        delete(z);
    }
    root->color = BLACK;
}

void LLRBTREE::deleteFix(Node* x)
{
    Node* sibling;

    while (x != root && x->color == BLACK)
    {
        if (x->parent == nullptr)
        {
            break;
        }

        bool isLeft = (x == x->parent->left);
        if (isLeft)
        {
            sibling = x->parent->right;
        }
        else
        {
            sibling = x->parent->left;
        }

        if (sibling == TNULL)
        {
            x = x->parent;
            continue;
        }

        if (sibling->color == RED)
        {
            sibling->color = BLACK;
            x->parent->color = RED;
            if (isLeft)
            {
                leftRotate(x->parent);
            }
            else
            {
                rightRotate(x->parent);
            }

            sibling = isLeft ? x->parent->right : x->parent->left;
        }

        if ((sibling->left == TNULL || sibling->left->color == BLACK) &&
            (sibling->right == TNULL || sibling->right->color == BLACK))
        {
            if (sibling != TNULL)
            {
                sibling->color = RED;
            }
            x = x->parent;
        }
        else
        {
            if (isLeft)
            {
                if (sibling->right == TNULL || sibling->right->color == BLACK)
                {
                    if (sibling->left != TNULL)
                    {
                        sibling->left->color = BLACK;
                    }
                    sibling->color = RED;
                    rightRotate(sibling);
                    sibling = x->parent->right;
                }

                sibling->color = x->parent->color;
                x->parent->color = BLACK;
                if (sibling->right != TNULL)
                {
                    sibling->right->color = BLACK;
                }
                leftRotate(x->parent);
                x = root;
            }
            else
            {
                if (sibling->left == TNULL || sibling->left->color == BLACK) // case 3
                {
                    if (sibling->right != TNULL)
                    {
                        sibling->right->color = BLACK;
                    }
                    sibling->color = RED;
                    leftRotate(sibling);
                    sibling = x->parent->left;
                }

                sibling->color = x->parent->color;
                x->parent->color = BLACK;
                if (sibling->left != TNULL)
                {
                    sibling->left->color = BLACK;
                }
                rightRotate(x->parent);
                x = root;
            }
        }
    }

    if (x != TNULL)
    {
        x->color = BLACK;
    }
}

void LLRBTREE::transplant(Node*& u, Node*& v)
{
    if (u->parent == nullptr)
    {
        root = v;
    }
    else if (u == u->parent->left)
    {
        u->parent->left = v;
    }
    else
    {
        u->parent->right = v;
    }

    v->parent = u->parent;
}

Node* LLRBTREE::successor(Node* node)
{
    if (node == TNULL) 
    {
        return TNULL;
    }

    while (node->left != TNULL)
    {
        node = node->left;
    }

    return node;
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
