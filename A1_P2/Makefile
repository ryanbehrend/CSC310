CC 			 := g++
CFLAGS 		 := -Wall -std=c++11

OBJS 		 := customErrorClass.o splay.o
DEPS 		 := customErrorClass.h splay.h

.PHONY: clean all

all: splay

clean:
	rm $(OBJS) splay

customErrorClass.o: customErrorClass.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

customErrorHandling.o: customErrorHandling.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

splay.o: splay.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

splay: $(OBJS) mainsplay.cpp
	$(CC) -o $@ $(CFLAGS) $^ 
