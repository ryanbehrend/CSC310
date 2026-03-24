#include "LLRB.h"

int main() {
    LLRBTREE rb;

    for (int i = 1; i <= 30; i++)
    {
        rb.insert(i);
    }

    cout << "Constructed RB tree:\n";
    rb.printTree();

    for (int i = 1; i <= 30; i += 5)
    {
        rb.remove(i);
    }

    cout << "Removed some elements:\n";
    rb.printTree();

    cout << "Total rotation count: " << rb.rotationCount << endl;

    return 0;
}
