For this project, I seperated the for files into their own folders. Each folder contains the .cpp file with the code, the make file, and the output screenshot

Task 4:
In terms of time complexity path copying and fat node strategies both are O(log n) for all the normal tree operations. The main difference is that the fat nodes straegies requires looping through the version history for that node. Finally, the lazy queue strategy differs since the queue doesn't have a tree structure. Instead it acheives a O(1) amortized cost because the large operations, reversing the rear list, only happens every now and then.

For memory usage, path copying create O(log n) new nodes for each operation. However, all of these are small nodes that don't take much space. For the fat node strategy, much fewer nodes need to be allocated, but the nodes that are allocated are much larger. Additionally, they can grow forever depending on how many versions are made. And for the lazy queue, the nodes are used again so we don't need to allocate new ones, we only need to keep track of two pointers.

Finally, in terms of structural sharing path copying maintains the majority of the previous structure, only making new nodes for the path that was taken. Fat nodes are great about structural sharing as they use the exact same nodes as other version, only creating new nodes when one doesn't already exist. For the lazy queue, only the front half of the structure is shared with the rear hald needing to be rebuilt for each version.
