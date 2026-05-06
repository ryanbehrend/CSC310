// persistant bst
// using path copying
// shared pointer
// keeps track of atomic refcount for delete()

#include <iostream>
#include <memory>
#include <atomic>

using namespace std;

struct Node
{
    int key;
    shared_ptr<Node> left;
    shared_ptr<Node> right;
    atomic<int> refcount;

    Node(int k, shared_ptr<Node> l = nullptr, shared_ptr<Node> r = nullptr)
    {
        key = k;
        left = l;
        right = r;
        refcount = 1;
    }
};

static shared_ptr<Node> makeNode(int k, shared_ptr<Node> l = nullptr, shared_ptr<Node> r = nullptr)
{
    auto node = make_shared<Node>(k, l, r);
    node->refcount.store(node.use_count());

    return node;
}

class persistantBST
{
private:
    shared_ptr<Node> root;

    shared_ptr<Node> insert(shared_ptr<Node> node, int key)
    {
        if (!node)
        {
            return makeNode(key);
        }

        if (key < node->key)
        {
            return makeNode(node->key, insert(node->left, key), node->right);
        }
        else if (key > node->key)
        {
            return makeNode(node->key, node->left, insert(node->right, key));
        }
        else
        {
            node->refcount.store(node.use_count());
            return node;
        }
    }

    shared_ptr<Node> remove(shared_ptr<Node> node, int key)
    {
        if (!node)
        {
            return nullptr;
        }

        if (key < node->key)
        {
            return makeNode(node->key, remove(node->left, key), node->right);
        }
        else if (key > node->key)
        {
            return makeNode(node->key, node->left, remove(node->right, key));
        }
        else
        {
            if (!node->left && !node->right)
            {
                return nullptr;
            }
            else if (!node->left)
            {
                node->right->refcount.store(node->right.use_count());

                return node->right;
            }
            else if (!node->right)
            {
                node->left->refcount.store(node->left.use_count());

                return node->left;
            }
            else
            {
                shared_ptr<Node> successor = node->right;
                while (successor->left)
                {
                    successor = successor->left;
                }

                return makeNode(successor->key, node->left, remove(node->right, successor->key));
            }
        }
    }

    bool search(shared_ptr<Node> node, int key)
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
        
        return false;
    }

    void inorder(shared_ptr<Node> node)
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

    persistantBST(shared_ptr<Node> r)
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
    cout << "Persistent BST (Path Copying, Shared Pointer, Atomic refcount)" << endl;

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
