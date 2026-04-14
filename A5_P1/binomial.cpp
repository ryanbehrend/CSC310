#include "binomial.h"
#include "customErrorClass.h"

binomialNode::binomialNode(int k)
{
    key = k;
    degree = 0;
    sibling = nullptr;
    child = nullptr;
    parent = nullptr;
}

// ---------------------- PRIVATE FUNCTIONS ------------------------------ //

binomialNode *BinomialHeap::unionHeap(binomialNode *heap1, binomialNode *heap2)
{
    if (!heap1)
    {
        return heap2;
    }
    if (!heap2)
    {
        return heap1;
    }

    binomialNode *newHead = nullptr;
    binomialNode **pos = &newHead;

    while (heap1 && heap2)
    {
        if (heap1->degree <= heap2->degree)
        {
            *pos = heap1;
            heap1 = heap1->sibling;
        }
        else
        {
            *pos = heap2;
            heap2 = heap2->sibling;
        }

        pos = &((*pos)->sibling);
    }

    *pos = (heap1) ? heap1 : heap2;

    return newHead;
}

binomialNode *BinomialHeap::mergeTrees(binomialNode *tree1, binomialNode *tree2)
{
    if (tree1->key > tree2->key)
    {
        swap(tree1, tree2);
    }

    tree2->parent = tree1;
    tree2->sibling = tree1->child;
    tree1->child = tree2;
    tree1->degree++;

    return tree1;
}

void BinomialHeap::linkTrees(binomialNode *&prev, binomialNode *&curr, binomialNode *&next)
{
    if (curr->degree != next->degree || next->sibling && next->sibling->degree == curr->degree)
    {
        prev = curr;
        curr = next;
    }
    else
    {
        if (curr->key <= next->key)
        {
            curr->sibling = next->sibling;
            mergeTrees(curr, next);
        }
        else
        {
            if (!prev)
            {
                head = next;
            }
            else
            {
                prev->sibling = next;
            }

            mergeTrees(next, curr);
            curr = next;
        }
    }
}

binomialNode *BinomialHeap::search(binomialNode *node, int key)
{
    if (!node)
        return nullptr;

    if (node->key == key)
        return node;

    // Check siblings
    binomialNode *found = search(node->sibling, key);
    if (found)
        return found;

    // Check children
    return search(node->child, key);
}

// ---------------- PUBLIC FUNCTIONS ------------------------------ //

BinomialHeap::BinomialHeap()
{
    head = nullptr;
}

void BinomialHeap::insert(int key)
{
    BinomialHeap tempHeap;
    tempHeap.head = new binomialNode(key);

    head = unionHeap(head, tempHeap.head);

    if (!head || !head->sibling)
    {
        return;
    }

    binomialNode *prev = nullptr;
    binomialNode *curr = head;
    binomialNode *next = curr->sibling;

    while (next)
    {
        linkTrees(prev, curr, next);
        next = curr->sibling;
    }
}

void BinomialHeap::merge(BinomialHeap &other)
{
    head = unionHeap(head, other.head);

    if (!head || !head->sibling)
    {
        return;
    }

    binomialNode *prev = nullptr;
    binomialNode *curr = head;
    binomialNode *next = curr->sibling;

    while (next)
    {
        linkTrees(prev, curr, next);
        next = curr->sibling;
    }
}

int BinomialHeap::findMin()
{
    if (!head)
    {
        return -1;
    }

    binomialNode *minNode = head;
    int minKey = head->key;

    binomialNode *temp = head->sibling;
    while (temp)
    {
        if (temp->key < minKey)
        {
            minNode = temp;
            minKey = temp->key;
        }

        temp = temp->sibling;
    }

    return minKey;
}

int BinomialHeap::deleteMin()
{
    if (!head)
    {
        throw MyException("can not delete from an empty heap");
    }

    binomialNode *curr = head;
    binomialNode *prev = nullptr;
    binomialNode *currMin = head;
    binomialNode *prevMin = nullptr;

    while (curr->sibling)
    {
        if (curr->sibling->key < currMin->key)
        {
            currMin = curr->sibling;
            prevMin = curr;
        }
        prev = curr;
        curr = curr->sibling;
    }

    int minKey = currMin->key;

    if (!prevMin)
    {
        head = currMin->sibling;
    }
    else
    {
        prevMin->sibling = currMin->sibling;
    }

    binomialNode *newHead = nullptr;
    binomialNode *child = currMin->child;

    while (child)
    {
        binomialNode *next = child->sibling;
        child->sibling = newHead;
        child->parent = nullptr;
        newHead = child;
        child = next;
    }

    head = unionHeap(head, newHead);

    if (head && head->sibling)
    {
        binomialNode *prev = nullptr;
        binomialNode *curr = head;
        binomialNode *next = curr->sibling;

        while (next)
        {
            linkTrees(prev, curr, next);
            next = curr->sibling;
        }
    }

    delete currMin;
    return minKey;
}

bool BinomialHeap::deleteKey(int key)
{
    if (!head)
    {
        throw MyException("can not delete from an empty heap");
    }

    binomialNode *curr = head;
    binomialNode *prev = nullptr;
    binomialNode *nodeToDelete = nullptr;
    binomialNode *prevNode = nullptr;

    while (curr)
    {
        if (curr->key == key)
        {
            nodeToDelete = curr;
            prevNode = prev;
            break;
        }
        prev = curr;
        curr = curr->sibling;
    }

    if (!nodeToDelete)
    {
        return false;
    }

    if (!prevNode)
    {
        head = nodeToDelete->sibling;
    }
    else
    {
        prevNode->sibling = nodeToDelete->sibling;
    }

    binomialNode *newHead = nullptr;
    binomialNode *child = nodeToDelete->child;

    while (child)
    {
        binomialNode *next = child->sibling;
        child->sibling = newHead;
        child->parent = nullptr;
        newHead = child;
        child = next;
    }

    head = unionHeap(head, newHead);

    if (head && head->sibling)
    {
        binomialNode *prev = nullptr;
        binomialNode *curr = head;
        binomialNode *next = curr->sibling;

        while (next)
        {
            linkTrees(prev, curr, next);
            next = curr->sibling;
        }
    }

    delete nodeToDelete;
    return true;
}

bool BinomialHeap::decreaseKey(int oldKey, int newKey)
{
    binomialNode *target = search(head, oldKey);

    if (!target)
    {
        return false;
    }

    if (newKey >= oldKey)
    {
        throw MyException("the new key must be smaller than the old key");
    }

    target->key = newKey;

    while (target->parent && target->key < target->parent->key)
    {
        swap(target->key, target->parent->key);
        target = target->parent;
    }

    return true;
}

void BinomialHeap::printHeap()
{
    cout << "Binomial Heap:\n";
    binomialNode *current = head;

    while (current != nullptr)
    {
        cout << endl
             << "Tree of degree " << current->degree << endl;
        printTree(current, 0);
        current = current->sibling;
    }
}

void BinomialHeap::printTree(binomialNode *node, int space)
{
    if (node == nullptr)
        return;

    cout << setw(space * 2) << node->key << endl;

    binomialNode *child = node->child;
    while (child)
    {
        printTree(child, space + 3);
        child = child->sibling;
    }
}
