Output (Task 5):
=== Small Graph Test ===
Running Baseline MST...
MST Cost: 14
Time taken: 8.738e-06 seconds

Running Optimized MST...
MST Cost: 14
Time taken: 5.473e-06 seconds

=== Large Graph Test (100000 nodes, 500000 edges) ===
Running Baseline MST...
MST Cost: 3750795
Time taken: 48.2158 seconds

Running Optimized MST...
MST Cost: 3750795
Time taken: 0.160058 seconds

Task 8:
How does the use of binomial heap improve the efficiency of Kruskal’s algorithm compared to a binary heap?
- The main reason binomial heaps improve the efficiency is due to it's O(log n) merge operation compared to the O(n) merge operation for binary heaps. Since Kruskal's algorithms relies heavily on the emrge operation, this is a major improvement.

How does the use of union-find with path compression and union by size improve the performance of Kruskal’s algorithm?
- Using path compression during the find() method ansures future lookups are nearly O(1) time. Additionally, union by size ensure the trees stay shallow so operations never take too long.

Explain your observations from timing both versions and discuss the time complexity of both versions of Kruskal's algorithm.
- The timing outputs were what was expected with the optimizaed verison of Kruskal's algorithm taking significantly less time while producing the same MST. The small graph test happened nearly instantly for both versions, but the optimized version speed up the larger graph by about 300 times. In terms of time complexity, the unoptimized version runs in O(n^2) time complexity and the optimized version runs in O(n * log n) time complexity.
