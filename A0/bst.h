using namespace std;

struct treenode
{
    int dat;
    treenode *lchild;
    treenode *rchild;
};

class BST
{
public:
    BST();
    void in();
    void pre();
    void post();
    void insert(int val);
    void remove(int val);
    bool search(int val);
    int treeHeight();
    int nodeHeight(int val);
    bool isBalanced();
    int numNodes();
    bool isWorstCaseSenario();

private:
    void inHelper(treenode *root);
    void preHelper(treenode *root);
    void postHelper(treenode *root);
    void insertHelper(treenode *root, int val);
    treenode *removeHelper(treenode *root, int val);
    bool searchHelper(treenode *root, int val);
    int treeHeightHelper(treenode *root);
    int nodeHeightHelper(treenode *root, int val);
    bool isBalancedHelper(treenode *root);
    int numNodesHelper(treenode *root);
    bool isWorstCaseSenarioHelper(treenode *root);
    treenode *root;
};
