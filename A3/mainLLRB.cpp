#include "LLRB.h"

int main() {
    RBTREE rb;

    for (int i = 1; i <= 30; i++)
    {
        rb.insert(i);
    }

    cout << "Constructed RB tree:\n";
    rb.printTree();

    cout << "Total rotation count: " << rb.rotationCount << endl;

    return 0;
}
