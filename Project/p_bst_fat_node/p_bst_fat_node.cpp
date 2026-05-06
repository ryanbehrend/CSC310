// persistant bst
// using fat nodes

#include <iostream>
#include <vector>

using namespace std;

struct Node
{
    int key;

    struct VersionedPtr
    {
        int version;
        Node* ptr;
    };

    vector<VersionedPtr> leftHistory;
    vector<VersionedPtr> rightHistory;

    Node(int k, int version, Node* l = nullptr, Node* r = nullptr)
    {
        key = k;

        leftHistory.push_back({version, l});
        rightHistory.push_back({version, r});
    }

    static Node* getPtr(const vector<VersionedPtr>& hist, int version)
    {
        for (int i = (int)hist.size() - 1; i >= 0; --i)
        {
            if (hist[i].version <= version)
            {
                return hist[i].ptr;
            }
        }

        return nullptr;
    }

    Node* getLeft(int version)  const
    {
        return getPtr(leftHistory,  version);
    }
    Node* getRight(int version) const
    {
        return getPtr(rightHistory, version);
    }

    void setLeft(int version,  Node* p)
    {
        leftHistory.push_back({version, p});
    }
    void setRight(int version, Node* p)
    {
        rightHistory.push_back({version, p});
    }
};

class persistantBST {
private:
    static int currentVersion;
    static vector<Node*> roots;

    int version;

    explicit persistantBST(int v)
    {
        version = v;
    }

    static Node* insert(Node* node, int key, int newVersion)
    {
        if (node == nullptr)
        {
            return new Node(key, newVersion);
        }

        if (key < node->key)
        {
            Node* newLeft = insert(node->getLeft(newVersion - 1), key, newVersion);
            node->setLeft(newVersion, newLeft);
        }
        else if (key > node->key)
        {
            Node* newRight = insert(node->getRight(newVersion - 1), key, newVersion);
            node->setRight(newVersion, newRight);
        }

        return node;
    }

    static int minKey(Node* node, int version)
    {
        while (node->getLeft(version) != nullptr)
        {
            node = node->getLeft(version);
        }

        return node->key;
    }

    static Node* remove(Node* node, int key, int newVersion)
    {
        if (node == nullptr)
        {
            return nullptr;
        }

        if (key < node->key)
        {
            Node* newLeft = remove(node->getLeft(newVersion - 1), key, newVersion);
            node->setLeft(newVersion, newLeft);

            return node;
        }
        else if (key > node->key)
        {
            Node* newRight = remove(node->getRight(newVersion - 1), key, newVersion);
            node->setRight(newVersion, newRight);
            
            return node;
        }
        else
        {
            Node* L = node->getLeft(newVersion - 1);
            Node* R = node->getRight(newVersion - 1);

            if (L == nullptr)
            {
                return R;
            }
            if (R == nullptr)
            {
                return L;
            }

            int sucKey = minKey(R, newVersion - 1);
            return new Node(sucKey, newVersion, L, remove(R, sucKey, newVersion));
        }
    }

    static bool search(Node* node, int key, int version)
    {
        if (node == nullptr)
        {
            return false;
        }
        if (key == node->key)
        {
            return true;
        }

        if (key < node->key)
        {
            return search(node->getLeft(version),  key, version);
        }
        return search(node->getRight(version), key, version);
    }

    static void inorder(Node* node, int version)
    {
        if (node == nullptr)
        {
            return;
        }

        inorder(node->getLeft(version), version);
        cout << node->key << " ";
        inorder(node->getRight(version), version);
    }

public:
    persistantBST()
    {
        version = 0;
    }

    persistantBST insert(int key) const
    {
        int newVersion = ++currentVersion;

        Node* newRoot = insert(roots[version], key, newVersion);
        roots.push_back(newRoot);

        return persistantBST(newVersion);
    }

    persistantBST remove(int key) const
    {
        int newVersion = ++currentVersion;

        Node* newRoot = remove(roots[version], key, newVersion);
        roots.push_back(newRoot);

        return persistantBST(newVersion);
    }

    bool search(int key) const
    {
        return search(roots[version], key, version);
    }

    void inorder() const
    {
        inorder(roots[version], version);
        cout << "\n";
    }

    int getVersion() const
    {
        return version;
    }
};

int persistantBST::currentVersion = 0;
vector<Node*> persistantBST::roots = { nullptr };

int main()
{
    cout << "Persistent BST (Fat Nodes)" << endl;

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
