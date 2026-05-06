// persistant bst
// using path copying

#include <iostream>

using namespace std;

struct Node
{
    int key;
    Node *left;
    Node *right;

    Node(int k, Node *l = nullptr, Node *r = nullptr)
    {
        key = k;
        left = l;
        right = r;
    }
};

class persistantBST
{
private:
    Node *root;

    Node *insert(Node *node, int key)
    {
        if (!node)
        {
            return new Node(key);
        }

        if (key < node->key)
        {
            return new Node(node->key, insert(node->left, key), node->right);
        }
        else if (key > node->key)
        {
            return new Node(node->key, node->left, insert(node->right, key));
        }
        else
        {
            return node;
        }
    }

    Node *remove(Node *node, int key)
    {
        if (!node)
        {
            return nullptr;
        }

        if (key < node->key)
        {
            return new Node(node->key, remove(node->left, key), node->right);
        }
        else if (key > node->key)
        {
            return new Node(node->key, node->left, remove(node->right, key));
        }
        else
        {
            if (!node->left && !node->right)
            {
                return nullptr;
            }
            else if (!node->left)
            {
                return node->right;
            }
            else if (!node->right)
            {
                return node->left;
            }
            else
            {
                Node *successor = node->right;
                while (successor->left)
                {
                    successor = successor->left;
                }

                return new Node(successor->key, node->left, remove(node->right, successor->key));
            }
        }
    }

    bool search(Node *node, int key)
    {
        if (!node)
        {
            return false;
        }
        if (key == node->key)
        {
            return true;
        }

        if (key < node->key)
        {
            return search(node->left, key);
        }
        if (key > node->key)
        {
            return search(node->right, key);
        }
    }

    void inorder(Node *node)
    {
        if (!node)
        {
            return;
        }

        inorder(node->left);
        cout << node->key << " ";
        inorder(node->right);
    }

public:
    persistantBST()
    {
        root = nullptr;
    }

    persistantBST(Node *r)
    {
        root = r;
    }

    persistantBST insert(int key)
    {
        return persistantBST(insert(root, key));
    }

    persistantBST remove(int key)
    {
        return persistantBST(remove(root, key));
    }

    bool search(int key)
    {
        return search(root, key);
    }

    void inorder()
    {
        inorder(root);
        cout << endl;
    }
};

int main()
{
    cout << "Persistent BST (Path Copying)" << endl;

    persistantBST t1;

    auto t2 = t1.insert(10);
    auto t3 = t2.insert(5);
    auto t4 = t3.insert(7);

    cout << "t3: ";
    t3.inorder();

    cout << "t4: ";
    t4.inorder();

    cout << "Removing 5 from t3 and 7 from t4" << endl;
    auto t5 = t3.remove(5);
    auto t6 = t4.remove(7);

    cout << "t5: ";
    t5.inorder();

    cout << "t6: ";
    t6.inorder();

    return 0;
}
