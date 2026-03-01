#ifndef DSW_H
#define DSW_H

#include <iostream>
#include <math.h>
#include <cstdlib> 
#include <ctime>

using namespace std;

struct Node
{
    int data;
    Node* left;
    Node* right;

    Node(int val)
    {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

class BST 
{
    private:
        Node* root;

        void rotateRight(Node*& node);
        void rotateLeft(Node*& node);
        int  subtreeSize(Node* root);
        void createVine();
        void rebuildTree(int size);
        void performRotation(int count, string direction);
        void printTree(Node* root, int space);

    public:
        BST();
        ~BST();

        void deleteTree(Node*& node);

        void insert(int val);
        void dswBalance();

        void display();

};

#endif
