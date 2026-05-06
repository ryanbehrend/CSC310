#include <iostream>
#include <memory>
using namespace std;

template <typename T>
struct Node
{
    T value;
    shared_ptr<Node<T>> next;

    Node(T val, shared_ptr<Node<T>> nxt = nullptr)
    {
        value = val;
        next = nxt;
    }
};

template <typename T>
shared_ptr<Node<T>> reverse(shared_ptr<Node<T>> head)
{
    shared_ptr<Node<T>> result = nullptr;

    while (head)
    {
        result = make_shared<Node<T>>(head->value, result);
        head = head->next;
    }

    return result;
}

template <typename T>
shared_ptr<Node<T>> concat(shared_ptr<Node<T>> a, shared_ptr<Node<T>> b)
{
    if (!a)
    {
        return b;
    }

    return make_shared<Node<T>>(a->value, concat(a->next, b));
}

template <typename T>
class persistantQueue
{
private:
    shared_ptr<Node<T>> front;
    shared_ptr<Node<T>> rear;
    shared_ptr<Node<T>> schedule;
    int frontSize;
    int rearSize;

    persistantQueue(shared_ptr<Node<T>> f, shared_ptr<Node<T>> r, shared_ptr<Node<T>> s, int fs, int rs)
    {
        front = f;
        rear = r;
        schedule = s;
        frontSize = fs;
        rearSize = rs;
    }

    persistantQueue advance() const
    {
        if (schedule)
        {
            return persistantQueue(front, rear, schedule->next, frontSize, rearSize);
        }

        auto newFront = concat(front, reverse(rear));
        
        return persistantQueue(newFront, nullptr, newFront, frontSize + rearSize, 0);
    }

public:
    persistantQueue()
    {
        front = nullptr;
        rear = nullptr;
        schedule = nullptr;
        frontSize = 0;
        rearSize = 0;
    }

    bool isEmpty() const
    {
        return frontSize == 0;
    }

    persistantQueue enqueue(T x) const
    {
        auto newRear = make_shared<Node<T>>(x, rear);
        return persistantQueue(front, newRear, schedule, frontSize, rearSize + 1).advance();
    }

    persistantQueue dequeue() const
    {
        if (isEmpty())
        {
            throw runtime_error("Queue is empty");
        }

        return persistantQueue(front->next, rear, schedule, frontSize - 1, rearSize).advance();
    }

    T peek() const
    {
        if (isEmpty())
        {
            throw runtime_error("Queue is empty");
        }

        return front->value;
    }

    int size() const
    {
        return frontSize + rearSize;
    }
};

int main()
{
    cout << "Persistent Queue" << endl;

    persistantQueue<int> q1;

    auto q2 = q1.enqueue(1);
    auto q3 = q2.enqueue(2);
    auto q4 = q3.enqueue(3);
    auto q5 = q4.enqueue(4);

    cout << "Front of each version:" << endl;
    cout << "q2: " << q2.peek() << endl;
    cout << "q3: " << q3.peek() << endl;
    cout << "q4: " << q4.peek() << endl;
    cout << "q5: " << q5.peek() << endl;

    cout << "Dequeueing from q3 and q5:" << endl;
    auto q6 = q3.dequeue();
    auto q7 = q5.dequeue();

    cout << "q6: " << q6.peek() << endl;
    cout << "q7: " << q7.peek() << endl;

    return 0;
}
