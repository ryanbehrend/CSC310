CC 			 := g++
CFLAGS 		 := -Wall -std=c++11

OBJS 		 := p_bst_p1.o
DEPS 		 := p_bst_p1.h

.PHONY: clean all

all: p_bst_p1

clean:
	rm $(OBJS) p_bst_p1

customErrorClass.o: customErrorClass.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

customErrorHandling.o: customErrorHandling.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

geneBank.o: p_bst_p1.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<
