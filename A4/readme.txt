Analysis:

For the No Collision dataset, the three chaning methods were provided very similar timings for insertion and search.
The two open addressing methods were significantly faster, taking about 120 microseconds less time.
And the last method, double hashing was slower than both of those at 207 microseconds for insertion and 79 microseconds for search.

For the Low Collision dataset, all the collision handling methods show very similar results as the No Collision dataset.

For the High Collision dataset, the three chaning methods imporved slightly, with fewer empty buckets meaning better memory locality.
The fourth method, linear probing, slowed the most due to clustering causing every operation to probe through long runs of keys.
The fifth method, quadratic probing, stay similar to before, meaning inceasing the choses index in a quadratic manner works much better than linearly.
Finally, the fifth method saw some small improvements in speed.

Output:

========================================
Benchmarking with data from: data/no_collision_data.txt
========================================

----------------------------------------
Running benchmark for method: 0
----------------------------------------
Insertion time: 199605 microseconds
Search time: 51481 microseconds
Deletion time: 0 microseconds

Statistics for method: 0
Total elements: 100000
Load factor: 0.499985
Empty buckets: 121427
Max chain length: 6

----------------------------------------
Running benchmark for method: 1
----------------------------------------
Insertion time: 170412 microseconds
Search time: 46012 microseconds
Deletion time: 0 microseconds

Statistics for method: 1
Total elements: 100000
Load factor: 0.499985
Empty buckets: 121427
Max chain length: 6

----------------------------------------
Running benchmark for method: 2
----------------------------------------
Insertion time: 209979 microseconds
Search time: 40509 microseconds
Deletion time: 0 microseconds

Statistics for method: 2
Total elements: 100000
Load factor: 0.499985
Empty buckets: 121427
Max chain length: 6

----------------------------------------
Running benchmark for method: 3
----------------------------------------
Insertion time: 119833 microseconds
Search time: 60058 microseconds
Deletion time: 0 microseconds

Statistics for method: 3
Total elements: 100000
Load factor: 0.499985
Empty buckets: 100006

----------------------------------------
Running benchmark for method: 4
----------------------------------------
Insertion time: 126254 microseconds
Search time: 57626 microseconds
Deletion time: 0 microseconds

Statistics for method: 4
Total elements: 100000
Load factor: 0.499985
Empty buckets: 100006

----------------------------------------
Running benchmark for method: 5
----------------------------------------
Insertion time: 207301 microseconds
Search time: 79369 microseconds
Deletion time: 0 microseconds

Statistics for method: 5
Total elements: 100000
Load factor: 0.499985
Empty buckets: 100006

----------------------------------------
Running benchmark for std::unordered_map
----------------------------------------
std::unordered_map Benchmark Results:
Insertion time: 54401 microseconds
Search time: 63030 microseconds
Deletion time: 0 microseconds

========================================
Benchmarking with data from: data/low_collision_data.txt
========================================

----------------------------------------
Running benchmark for method: 0
----------------------------------------
Insertion time: 154190 microseconds
Search time: 36008 microseconds
Deletion time: 0 microseconds

Statistics for method: 0
Total elements: 100000
Load factor: 0.499985
Empty buckets: 121207
Max chain length: 6

----------------------------------------
Running benchmark for method: 1
----------------------------------------
Insertion time: 165704 microseconds
Search time: 38005 microseconds
Deletion time: 0 microseconds

Statistics for method: 1
Total elements: 100000
Load factor: 0.499985
Empty buckets: 121207
Max chain length: 6

----------------------------------------
Running benchmark for method: 2
----------------------------------------
Insertion time: 175914 microseconds
Search time: 40862 microseconds
Deletion time: 0 microseconds

Statistics for method: 2
Total elements: 100000
Load factor: 0.499985
Empty buckets: 121207
Max chain length: 6

----------------------------------------
Running benchmark for method: 3
----------------------------------------
Insertion time: 104800 microseconds
Search time: 46660 microseconds
Deletion time: 0 microseconds

Statistics for method: 3
Total elements: 100000
Load factor: 0.499985
Empty buckets: 100006

----------------------------------------
Running benchmark for method: 4
----------------------------------------
Insertion time: 121217 microseconds
Search time: 50737 microseconds
Deletion time: 0 microseconds

Statistics for method: 4
Total elements: 100000
Load factor: 0.499985
Empty buckets: 100006

----------------------------------------
Running benchmark for method: 5
----------------------------------------
Insertion time: 189101 microseconds
Search time: 81023 microseconds
Deletion time: 0 microseconds

Statistics for method: 5
Total elements: 100000
Load factor: 0.499985
Empty buckets: 100006

----------------------------------------
Running benchmark for std::unordered_map
----------------------------------------
std::unordered_map Benchmark Results:
Insertion time: 52922 microseconds
Search time: 57553 microseconds
Deletion time: 0 microseconds

========================================
Benchmarking with data from: data/high_collision_data.txt
========================================

----------------------------------------
Running benchmark for method: 0
----------------------------------------
Insertion time: 118461 microseconds
Search time: 37246 microseconds
Deletion time: 0 microseconds

Statistics for method: 0
Total elements: 100000
Load factor: 0.499985
Empty buckets: 120813
Max chain length: 5

----------------------------------------
Running benchmark for method: 1
----------------------------------------
Insertion time: 89427 microseconds
Search time: 41179 microseconds
Deletion time: 0 microseconds

Statistics for method: 1
Total elements: 100000
Load factor: 0.499985
Empty buckets: 120813
Max chain length: 5

----------------------------------------
Running benchmark for method: 2
----------------------------------------
Insertion time: 125161 microseconds
Search time: 43655 microseconds
Deletion time: 0 microseconds

Statistics for method: 2
Total elements: 100000
Load factor: 0.499985
Empty buckets: 120813
Max chain length: 5

----------------------------------------
Running benchmark for method: 3
----------------------------------------
Insertion time: 356490 microseconds
Search time: 130276 microseconds
Deletion time: 0 microseconds

Statistics for method: 3
Total elements: 100000
Load factor: 0.499985
Empty buckets: 100006

----------------------------------------
Running benchmark for method: 4
----------------------------------------
Insertion time: 117665 microseconds
Search time: 53905 microseconds
Deletion time: 0 microseconds

Statistics for method: 4
Total elements: 100000
Load factor: 0.499985
Empty buckets: 100006

----------------------------------------
Running benchmark for method: 5
----------------------------------------
Insertion time: 152112 microseconds
Search time: 62145 microseconds
Deletion time: 0 microseconds

Statistics for method: 5
Total elements: 100000
Load factor: 0.499985
Empty buckets: 100006

----------------------------------------
Running benchmark for std::unordered_map
----------------------------------------
std::unordered_map Benchmark Results:
Insertion time: 59218 microseconds
Search time: 47626 microseconds
Deletion time: 0 microseconds
