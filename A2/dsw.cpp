#include "dsw.h"

// ----------------- PRIVATE ----------------------------------

// when left-heavy tree
void BST::rotateRight(Node*& node) // passing the parent
{
    if(node == nullptr || node->left == nullptr)
    {
        return;
    }
    
    // get the node to rotate R
    Node* leftChild = node->left; 
    // 1) leftnode's right child is going to become parent's left child
    node->left = leftChild->right;
    // 2) parent is going to be right child of node that is rotated
    leftChild->right = node;
    
    node = leftChild;
}

// when right-heavy
void BST::rotateLeft(Node*& node)
{
    if(node == nullptr || node->right == nullptr)
    {
        return;
    }

    // get the node to rotate L
    Node* rightChild = node->right;
    // 1) rightnode's left child is going to become parent's right child
    node->right = rightChild->left;
    // 2) parent is going to be left child of node that is rotated
    rightChild->left = node;

    node = rightChild;
}

int BST::subtreeSize(Node* root)
{
    if (root == nullptr)
    {
        return 0;
    }

    return subtreeSize(root->left) + subtreeSize(root->right) + 1;
}

void BST::createVine()
{
    if (root == nullptr)
    {
        return;
    }

    Node* grandparent = nullptr;
    Node* parent = root;
    Node* child = root->left;

    while (parent != nullptr)
    {
        if (child != nullptr)
        {
            int size = subtreeSize(child);

            if (size <= 2)
            {
                grandparent = parent;
                parent = parent->left;
                if (parent != nullptr)
                {
                    child = parent->left;
                }
            }
            else
            {
                rotateRight(parent);
                if (grandparent == nullptr)
                {
                    root = parent;
                }
                else
                {
                    grandparent->left = parent;
                }
                child = parent->left;
            }
        }
        else
        {
            grandparent = parent;
            parent = parent->left;
            if (parent != nullptr)
            {
                child = parent->left;
            }
        }
    }
}

void BST::rebuildTree(int size)
{
    if (size <= 1)
    {
        return;
    }

    int h = (int)(2.0 * log2(size));
    int passes = h / 2;

    for (int pass = 0; pass < passes; pass++)
    {
        int count = size / (1 << (pass + 1));
        if (count < 1)
        {
            break;
        }

        performRotation(count, "left");

        if (pass % 2 == 1)
        {
            int lcount = count / 2;
            if (lcount >= 1)
            {
                performRotation(lcount, "right");
            }
        }
    }
}

void BST::performRotation(int count, string direction)
{
    Node *grandparent = nullptr;
    Node *parent = root;

    if (direction == "right")
    {
        for (int i = 0; i < count; i++)
        {
            if (parent == nullptr || parent->left == nullptr)
            {
                break;
            }

            Node *child = parent->left;

            parent->left = child->right;
            child->right = parent;

            if (grandparent == nullptr)
            {
                root = child;
            }
            else
            {
                grandparent->left = child;
            }

            grandparent = child;
            parent = child->right;
        }
    }
    else
    {
        for (int i = 0; i < count; i++)
        {
            if (parent == nullptr || parent->right == nullptr)
            {
                break;
            }

            Node *child = parent->right;

            parent->right = child->left;
            child->left = parent;

            if (grandparent == nullptr)
            {
                root = child;
            }
            else
            {
                grandparent->right = child;
            }

            grandparent = child;
            parent = child->right;
        }
    }  
}

void BST::printTree(Node* root, int space) {
    const int COUNT = 10; 

    if (root == nullptr)
    {
        return;
    }

    // Increase the distance between levels
    space += COUNT;

    // Print the right child first (to appear on top)
    printTree(root->right, space);

    // Print the current node after right child

    for (int i = COUNT; i < space; i++)
    {
        cout << " "; // Indentation for tree depth
    }
    cout << root->data << endl;

    // Print the left child
    printTree(root->left, space);
}

// --------------------- PUBLIC ------------------
BST::BST()
{
    root = nullptr;
}

BST::~BST()
{
    deleteTree(root);
}

void BST::deleteTree(Node*& node)
{
    if(node == nullptr)
    {
        return;
    }
    
    deleteTree(node->left);
    deleteTree(node->right);

    delete node;
}

void BST::insert(int val)
{
    Node* newNode = new Node(val);
    if(root == nullptr)
    {
        root = newNode;
        return;
    }
    
    Node* curr = root;
    Node*parent = nullptr;

    while(curr != nullptr)
    {
        parent = curr;
        if(val < curr->data)
        {
            curr = curr->left;
        }
        else
        {
            curr = curr->right;
        }
    }

    if(val < parent->data)
    {
        parent->left = newNode;
    }
    else
    {
        parent->right = newNode;
    }
}

void BST::dswBalance()
{
    if (root == nullptr)
    {
        return;
    }

    // phase 1
    createVine();

    cout << "After Phase 1:";
    display();

    int size = 0;
    Node* temp = root;
    while (temp != nullptr)
    {
        size++;
        temp = temp->right;
    }

    // Phase 2
    rebuildTree(size);
}


void BST::display()
{
    cout << endl;
    printTree(root, 0);
    cout << endl;
}