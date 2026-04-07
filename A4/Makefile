CC 			 := g++
CFLAGS 		 := -Wall -std=c++11

OBJS 		 := customErrorClass.o hash.o AVL/avl.o
DEPS 		 := customErrorClass.h hash.h AVL/avl.h

.PHONY: clean all

all: hash

clean:
	rm $(OBJS) hash

customErrorClass.o: customErrorClass.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

customErrorHandling.o: customErrorHandling.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

hash.o: hash.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

AVL/avl.o: AVL/avl.cpp AVL/avl.h
	$(CC) -c -o $@ $(CFLAGS) $<

hash: $(OBJS) mainHash.cpp
	$(CC) -o $@ $(CFLAGS) $^ 
