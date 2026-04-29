CC 			 := g++
CFLAGS 		 := -Wall -std=c++11

OBJS 		 := customErrorClass.o geneBank.o
DEPS 		 := customErrorClass.h geneBank.h

.PHONY: clean all

all: geneBank

clean:
	rm $(OBJS) geneBank

customErrorClass.o: customErrorClass.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

customErrorHandling.o: customErrorHandling.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

geneBank.o: geneBank.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

geneBank: $(OBJS) mainSamples.cpp
	$(CC) -o $@ $(CFLAGS) $^ 
