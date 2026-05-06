CC 			 := g++
CFLAGS 		 := -Wall -std=c++11

OBJS 		 := p_bst_fat_node.o
DEPS 		 := p_bst_fat_node.h

.PHONY: clean all

all: p_bst_fat_node

clean:
	rm $(OBJS) p_bst_fat_node

customErrorClass.o: customErrorClass.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

customErrorHandling.o: customErrorHandling.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

geneBank.o: p_bst_fat_node.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<
