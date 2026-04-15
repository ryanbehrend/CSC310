This code inserts 32 random numbers between 1-100 into a binomial heap
I did this because it results in a binomial heap with only one tree of degree 5, meaning removing will properly test restructuring the binomial heap

Then it deletes the minimum number in the heap and prints it out

Then it enters a do-while loop and generates random numbers between 1-100, attempting to delete them
If the generated number is in the binomial heap, it will be deleted. Otherwise, it will generate a new number and try again

Finally, it enters another do-while loop and generates random numbers between 1-100, attempting to decrease them
To test, I just attempt to decrement each number by 1. If the generated number is not in the binomial heap, it will repeat and try again
