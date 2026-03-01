#include "splay.h"
#include "customErrorClass.h"

// Constructor

SplayTree::SplayTree() 
{
    root = nullptr; 
}


// Public Functions

void SplayTree::display()
{
    printTree(root, 0);
    cout << endl;
}

void SplayTree::insert(int key)
{
    insertNode(key);
}

void SplayTree::remove(int key)
{
    root = deleteNode(root, key);
}

bool SplayTree::search(int key)
{
    return searchNode(key);
}


// Private Functions

SplayTree::Node* SplayTree::bottomUpRotateRight(Node* x)
{
    rotationCount++;

    Node* y = x->left;
    x->left = y->right;

    if (y->right)
    {
        y->right->parent = x;
    }

    Node* p = x->parent;   // capture old parent

    y->parent = p;
    if (!p)
    {
        root = y;
    }
    else if (p->left == x)
    {
        p->left = y;
    }
    else
    {
        p->right = y;
    }

    y->right = x;
    x->parent = y;

    return y;
}

SplayTree::Node* SplayTree::bottomUpRotateLeft(Node* x)
{
    rotationCount++;

    Node* y = x->right;
    x->right = y->left;

    if (y->left)
    {
        y->left->parent = x;
    }

    Node* p = x->parent;

    y->parent = p;
    if (!p)
    {
        root = y;
    }
    else if (p->left == x)
    {
        p->left = y;
    }
    else
    {
        p->right = y;
    }

    y->left = x;
    x->parent = y;

    return y;
}

SplayTree::Node* SplayTree::topDownRotateRight(Node* x)
{
    rotationCount++;

    Node* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

SplayTree::Node* SplayTree::topDownRotateLeft(Node* x)
{
    rotationCount++;

    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}

void SplayTree::bottomUpSplay(Node* x)
{
    if (!x)
    {
        return;
    }

    while (x->parent != nullptr)
    {
        Node* p = x->parent;
        Node* g = p->parent;

        if (!g)
        {
            if (p->left == x) // Zig
            {
                bottomUpRotateRight(p);
            }
            else // Zag
            {
                bottomUpRotateLeft(p);
            }
        }

        else if (g->left == p && p->left == x) // Zig-Zig
        {
            bottomUpRotateRight(g);
            bottomUpRotateRight(p);
        }
        else if (g->right == p && p->right == x) // Zag-Zag
        {
            bottomUpRotateLeft(g);
            bottomUpRotateLeft(p);
        }

        else if (g->left == p && p->right == x) // Zig-Zag
        {
            bottomUpRotateLeft(p);
            bottomUpRotateRight(g);
        }
        else // Zag-Zig
        {
            bottomUpRotateRight(p);
            bottomUpRotateLeft(g);
        }
    }

    root = x;
}

SplayTree::Node* SplayTree::topDownSplay(Node* root, int key)
{
    if (!root)
    {
        return nullptr;
    }

    Node header(0);
    Node* LeftTreeMax = &header;
    Node* RightTreeMin = &header;

    while (true)
    {
        if (key < root->key)
        {
            if (!root->left) // Zig
            {
                break;
            }

            if (key < root->left->key) // Zig-Zig
            {
                root = topDownRotateRight(root);
                if (!root->left)
                {
                    break;
                }
            }

            // Zig-Zag
            RightTreeMin->left = root;
            RightTreeMin = root;
            root = root->left;
        }
        else if (key > root->key)
        {
            if (!root->right) // Zag
            {
                break;
            }

            if (key > root->right->key) // Zag-Zag
            {
                root = topDownRotateLeft(root);
                if (!root->right)
                {
                    break;
                }
            }

            // Zag-Zig
            LeftTreeMax->right = root;
            LeftTreeMax = root;
            root = root->right;
        }
        else
        {
            break;
        }
    }

    // Final step of Zig, Zag, Zig-Zag, and Zag-Zig
    LeftTreeMax->right = root->left;
    RightTreeMin->left = root->right;

    root->left = header.right;
    root->right = header.left;

    return root;
}

SplayTree::Node* SplayTree::semiSplay(Node* root, int key, int maxRotations)
{
    if (!root)
    {
        return nullptr;
    }

    Node header(0);  
    Node* LeftTreeMax = &header;
    Node* RightTreeMin = &header;

    int rotations = 0;

    while (true)
    {
        if (key < root->key)
        {
            if (!root->left) // Zig
            {
                break;
            }

            if (key < root->left->key) // Zig-Zig
            {
                root = topDownRotateRight(root);
                rotations++;
                if (rotations >= maxRotations)
                {
                    break;
                }

                if (!root->left)
                {
                    break;
                }
            }

            // Zig-Zag
            RightTreeMin->left = root;
            RightTreeMin = root;
            root = root->left;
        }
        else if (key > root->key)
        {
            if (!root->right) // Zag
            {
                break;
            }

            if (key > root->right->key) // Zag-Zag
            {
                root = topDownRotateLeft(root);
                rotations++;
                if (rotations >= maxRotations)
                {
                    break;
                }
                if (!root->right)
                {
                    break;
                }
            }

            // Zag-Zig
            LeftTreeMax->right = root;
            LeftTreeMax = root;
            root = root->right;
        }
        else
        {
            break;
        }

        if (rotations >= maxRotations)
        {
            break;
        }
    }

    // Final step of Zig, Zag, Zig-Zag, and Zag-Zig
    LeftTreeMax->right = root->left;
    RightTreeMin->left = root->right;

    root->left = header.right;
    root->right = header.left;

    return root;
}

SplayTree::Node* SplayTree::weightedSplay(Node* root, int key)
{
    if (!root)
    {
        return nullptr;
    }

    Node header(0);
    Node* LeftTreeMax = &header;
    Node* RightTreeMin = &header;

    while (true)
    {
        if (key < root->key)
        {
            if (!root->left) // Zig
            {
                break;
            }

            if (root->left->weight >= root->weight)
            {
                if (key < root->left->key) // Zig-Zig
                {
                    root = topDownRotateRight(root);
                    if (!root->left)
                    {
                        break;
                    }
                }
            }

            // Zig-Zag
            RightTreeMin->left = root;
            RightTreeMin = root;
            root = root->left;
        }
        else if (key > root->key)
        {
            if (!root->right) // Zag
            {
                break;
            }

            if (root->right->weight >= root->weight)
            {
                if (key > root->right->key) // Zag-Zag
                {
                    root = topDownRotateLeft(root);
                    if (!root->right)
                    {
                        break;
                    }
                }
            }

            // Zag-Zig
            LeftTreeMax->right = root;
            LeftTreeMax = root;
            root = root->right;
        }
        else // if the key is found, increase weight
        {
            root->weight++;
            break;
        }
    }

    // Final step of Zig, Zag, Zig-Zag, and Zag-Zig
    LeftTreeMax->right = root->left;
    RightTreeMin->left = root->right;

    root->left = header.right;
    root->right = header.left;

    return root;
}

void SplayTree::insertNode(int key)
{
    if (!root)
    {
        root = new Node(key);
        return;
    }

    Node* curr = root;
    Node* parent = nullptr;
    
    while(curr)
    {
        parent = curr;
        if (key == curr->key)
        {
            return;
        }
        if (key < curr->key)
        {
            curr = curr->left;
        }
        else
        {
            curr = curr->right;
        }
    }

    Node* n = new Node(key);
    n->parent = parent;

    if (key < parent->key)
    {
        parent->left = n;
    }
    else
    {
        parent->right = n;
    }

    bottomUpSplay(n);
    //root = topDownSplay(root, key);
    //root = semiSplay(root, key, 2);
    //root = weightedSplay(root, key);
}

SplayTree::Node* SplayTree::deleteNode(Node* root, int key)
{
    if (!root)
    {
        return nullptr;
    }

    root = topDownSplay(root, key);
    this->root = root;

    if (!root || root->key != key)
    {
        return root;
    }

    Node* left = root->left;
    Node* right = root->right;

    delete root;

    if (!left)
    {
        if (right)
        {
            right->parent = nullptr;
        }
        return this->root = right;
    }

    Node* x = left;
    while (x->right)
    {
        x = x->right;
    }

    left = topDownSplay(left, x->key);

    left->right = right;
    return this->root = left;
}

bool SplayTree::searchNode(int key)
{
    searchCount++;

    if (!root)
    {
        return false;
    }

    int depth = 0;
    Node* curr = root;

    while (curr)
    {
        depth++;

        if (key == curr->key)
        {
            break;
        }

        if (key < curr->key)
        {
            curr = curr->left;
        }
        else
        {
            curr = curr->right;
        }
    }

    totalSearchDepth += depth;

    root = topDownSplay(root, key);

    return root->key == key;
}

void SplayTree::printTree(Node* root, int space)
{
    const int COUNT = 10; 

    if (root == nullptr)
    {
        return;
    }

    space += COUNT;

    printTree(root->right, space);

    for (int i = COUNT; i < space; i++)
    {
        cout << " ";
    }
    cout << root->key << endl;

    printTree(root->left, space);
}
