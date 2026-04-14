#include "binomial.h"
#include <cstdlib>
#include <ctime>

int randomNum(int min, int max)
{
    int num = rand() % (max - min + 1) + min;
    return num;
}

int main()
{
    BinomialHeap bh;

    srand(time(NULL));

    for (int i = 0; i < 32; i++)
    {
        bh.insert(randomNum(1, 100));
    }

    cout << "Inserted the numbers 32 random numbers betwee 1-100 into the binomial heap" << endl;
    bh.printHeap();
    cout << endl;
    cout << endl;

    cout << "Deleting the minimum number from the binomial heap: " << bh.deleteMin() << endl;
    bh.printHeap();
    cout << endl;
    cout << endl;

    int num;
    do
    {
        num = randomNum(1, 100);
        cout << "Attempting to delete " << num << " from the binomial heap" << endl;
    } while (!bh.deleteKey(num));
    bh.printHeap();
    cout << endl;
    cout << endl;

    do
    {
        num = randomNum(1, 100);
        cout << "Attempting to decrease " << num << " by 1" << endl;
    } while (!bh.decreaseKey(num, num - 1));
    bh.printHeap();
    cout << endl;
    cout << endl;

    return 0;
}
