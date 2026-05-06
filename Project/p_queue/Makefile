CC 			 := g++
CFLAGS 		 := -Wall -std=c++11

OBJS 		 := p_queue.o
DEPS 		 := p_queue.h

.PHONY: clean all

all: p_queue

clean:
	rm $(OBJS) p_queue

customErrorClass.o: customErrorClass.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

customErrorHandling.o: customErrorHandling.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

geneBank.o: p_queue.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<
