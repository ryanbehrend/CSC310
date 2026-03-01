#ifndef SPLAYTREE_H
#define SPLAYTREE_H

#include <iostream>
using namespace std;

class SplayTree
{
    private:
        struct Node
        {
            int key;
            int weight;
            Node* left;
            Node* right;
            Node* parent;
            Node(int k)
            {
                key = k;
                weight = 0;
                left = nullptr;
                right = nullptr; 
                parent = nullptr;
            }
        };

        Node* root;

        Node* bottomUpRotateRight(Node* x);
        Node* bottomUpRotateLeft(Node* x);
        Node* topDownRotateRight(Node* x);
        Node* topDownRotateLeft(Node* x);

        void  bottomUpSplay(Node* x);
        Node* topDownSplay(Node* root, int key);
        Node* semiSplay(Node* root, int key, int maxRotations);
        Node* weightedSplay(Node* root, int key);

        void  insertNode(int key);
        Node* deleteNode(Node* root, int key);
        bool  searchNode(int key);

        void  printTree(Node* root, int space);

    public:
        SplayTree();

        void insert(int key);
        void remove(int key);
        bool search(int key);

        void display();
        
        long rotationCount = 0;
        long totalSearchDepth = 0;
        long searchCount = 0;
};

#endif 
