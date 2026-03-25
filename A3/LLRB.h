#ifndef LLRBTREE_H
#define LLRBTREE_H

#include <iostream>

using namespace std;

// ANSI escape codes for colors
#define RED_COLOR "\033[1;31m"
#define BLACK_COLOR "\033[1;30m"
#define RESET_COLOR "\033[0m"

// group of constants
enum Color {RED, BLACK};

struct Node
{
    int data;
    Color color;
    Node* left;
    Node* right;

    Node(int key)
    {
        data = key;
        color = RED;
        left = nullptr;
        right = nullptr;
    }
};

class LLRBTREE
{
    private:
        Node* root;
        Node* TNULL;

        void leftRotate(Node*& node);
        void rightRotate(Node*& node);

        bool isRed(Node* node);
        void flipColor(Node* node);

        void insert(Node*& node, int data);

        void deleteSubtree(Node* node);
        void print(Node* root, int space);

    public:
        LLRBTREE();
        ~LLRBTREE();

        void insert(int data);
        void printTree();

        int rotationCount = 0;
};

#endif
