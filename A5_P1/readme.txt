This code inserts 32 random numbers between 1-100 into a binomial heap
I did this because it results in a binomial heap with only one tree of degree 5, meaning removing will properly test restructuring the binomial heap

Then it deletes the minimum number in the heap and prints it out

Then it enters a do-while loop and generates random numbers between 1-100, attempting to delete them
If the generated number is in the binomial heap, it will be deleted. Otherwise, it will generate a new number and try again

Finally, it enters another do-while loop and generates random numbers between 1-100, attempting to decrease them
To test, I just attempt to decrement each number by 1. If the generated number is not in the binomial heap, it will repeat and try again


Task 6:
- How do binomial heaps improve the efficiency of merge operations compared to binary heaps.
Binomial heaps improve the efficiency of merge operations by combining trees of equal degree, reducing the time complexity to O(log n). This is much faster than binary heaps which merge by inserting one by one with a time complexity of O(n log n).

- Explain the time complexity of various operations in binomial heaps.
The worst case time complexity of all binomial heap operations is O(log n). However, the amortized time complexity is O(1) for insert and find-min, assuming it is optimized.

- Why do we use the left-child right-sibling representation in binomial heaps instead of traditional tree structures? How does it help with efficiency?
We use this representations because it simplifies the tree structure, making the linking of nodes simpler and more memory efficient. It allows trees to merge in O(1) time complexity for each link.

- What is your opinion on this? https://ieeexplore.ieee.org/abstract/document/7275881
