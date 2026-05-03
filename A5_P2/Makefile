CC 			 := g++
CFLAGS 		 := -Wall -std=c++11

OBJS 		 := customErrorClass.o mst.o binaryHeap.o binomialHeap.o
DEPS 		 := customErrorClass.h mst.h binaryHeap.h binomialHeap.h

.PHONY: clean all

all: mst

clean:
	rm $(OBJS) mst

customErrorClass.o: customErrorClass.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

customErrorHandling.o: customErrorHandling.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

mst.o: mst.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

binaryHeap.o: binaryHeap.cpp binaryHeap.h
	$(CC) -c -o $@ $(CFLAGS) $<

binomialHeap.o: binomialHeap.cpp binomialHeap.h
	$(CC) -c -o $@ $(CFLAGS) $<

mst: $(OBJS) main.cpp
	$(CC) -o $@ $(CFLAGS) $^ 
