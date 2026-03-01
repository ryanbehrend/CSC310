#include "dsw.h"

int main()
{
    BST bst;

    srand(time(nullptr));

    for (int i = 0; i < 20; i++)
    {
        int value = rand() % 100;
        bst.insert(value);
    }

    cout << "Orginal BST:";
    bst.display();

    bst.dswBalance();

    cout << "DSW balanced BST:";
    bst.display();

    
    return 0;
}
