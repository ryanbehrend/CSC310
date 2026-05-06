CC 			 := g++
CFLAGS 		 := -Wall -std=c++11

OBJS 		 := p_bst_p2.o
DEPS 		 := p_bst_p2.h

.PHONY: clean all

all: p_bst_p2

clean:
	rm $(OBJS) p_bst_p2

customErrorClass.o: customErrorClass.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

customErrorHandling.o: customErrorHandling.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

geneBank.o: p_bst_p2.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<
