#include <iostream>
#include "bst.h"
#include "customErrorClass.h"

using namespace std;

int main(int argc, char *argv[])
{
    BST t1, t2;

    t1.insert(4);
    t1.insert(2);
    t1.insert(6);
    t1.insert(1);
    t1.insert(3);
    t1.insert(5);
    t1.insert(7);

    t2.insert(1);
    t2.insert(2);
    t2.insert(3);
    t2.insert(4);
    t2.insert(5);
    t2.insert(6);
    t2.insert(7);

    cout << "In Order Traversal" << endl;
    try 
    {
        t1.in();
    }
    catch (MyException &e)
    {
       cout << "Error: " << e.what() << endl;
    }
    try 
    {
        t2.in();
    }
    catch (MyException &e)
    {
       cout << "Error: " << e.what() << endl;
    }


    cout << "\nPre Order Traversal" << endl;
    try 
    {
        t1.pre();
    }
    catch (MyException &e)
    {
        cout << "Error: " << e.what() << endl;
    }
    try 
    {
        t2.pre();
    }
    catch (MyException &e)
    {
        cout << "Error: " << e.what() << endl;
    }


    cout << "\nPost Order Traversal" << endl;
    try 
    {
        t1.post();
    }
    catch (MyException &e)
    {
        cout << "Error: " << e.what() << endl;
    }
    try 
    {
        t2.post();
    }
    catch (MyException &e)
    {
        cout << "Error: " << e.what() << endl;
    }


    try
    {
        if (t1.isBalanced())
        {
            cout << "\nt1 is balanced" << endl;
        }
        else
        {
            cout << "\nt1 is not balanced" << endl;
        }
    }
    catch (MyException &e)
    {
        cout << "Error: " << e.what() << endl;
    }
    try
    {
        if (t2.isBalanced())
        {
            cout << "\nt1 is balanced" << endl;
        }
        else
        {
            cout << "\nt1 is not balanced" << endl;
        }
    }
    catch (MyException &e)
    {
        cout << "Error: " << e.what() << endl;
    }


    try
    {
        int x = t1.treeHeight();
        cout << "\nt1 has a height of " << x << endl;
    }
    catch (MyException &e)
    {
        cout << "Error: " << e.what() << endl;
    }
    try
    {
        int x = t2.treeHeight();
        cout << "t2 has a height of " << x << endl;
    }
    catch (MyException &e)
    {
        cout << "Error: " << e.what() << endl;
    }


    try
    {
        int x = t1.nodeHeight(4);
        cout << "\nIn t1, the node with a value of 4 has a height of " << x << endl;
    }
    catch (MyException &e)
    {
        cout << "Error: " << e.what() << endl;
    }
    try
    {
        int x = t2.nodeHeight(4);
        cout << "In t2, the node with a value of 4 has a height of " << x << endl;
    }
    catch (MyException &e)
    {
        cout << "Error: " << e.what() << endl;
    }

    try
    {
        if (t1.isWorstCaseSenario())
        {
            cout << "\nt1 is in the worst case senario" << endl;
        }
        else
        {
            cout << "\nt1 is not in the worst case senario" << endl;
        }
    }
    catch (MyException &e)
    {
        cout << "Error: " << e.what() << endl;
    }
    try
    {
        if (t2.isWorstCaseSenario())
        {
            cout << "\nt2 is in the worst case senario" << endl;
        }
        else
        {
            cout << "\nt2 is not in the worst case senario" << endl;
        }
    }
    catch (MyException &e)
    {
        cout << "Error: " << e.what() << endl;
    }
    
}
