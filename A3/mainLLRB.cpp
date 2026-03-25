#include "LLRB.h"
#include "customErrorClass.h"
#include <cstdlib>
#include <ctime>

int main()
{
    try
    {
        LLRBTREE rb;

        srand(time(0));

        for (int i = 0; i < 30; i++)
        {
            int randomNum = rand() % 100 + 1;
            rb.insert(randomNum);
            cout << "LLRB tree after inserting " << randomNum << ":";
            rb.printTree();
        }

        cout << "Total rotation count: " << rb.rotationCount << endl;
    }
    catch (MyException &e)
    {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
