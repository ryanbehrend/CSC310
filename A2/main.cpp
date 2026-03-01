#include "dsw.h"

#include <cstdlib> 
#include <ctime>

int main()
{
    BST bst;

    for (int i = 0; i < 20; i++)
    {
        int value = std::rand() % 100;
        bst.insert(value);
    }

    cout << "Orginal BST:";
    bst.display();

    bst.dswBalance();

    cout << "DSW balanced BST:";
    bst.display();

    
    return 0;
}
