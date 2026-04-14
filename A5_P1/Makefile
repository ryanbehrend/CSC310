CC 			 := g++
CFLAGS 		 := -Wall -std=c++11

OBJS 		 := customErrorClass.o binomial.o
DEPS 		 := customErrorClass.h binomial.h

.PHONY: clean all

all: binomial

clean:
	rm $(OBJS) binomial

customErrorClass.o: customErrorClass.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

customErrorHandling.o: customErrorHandling.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

binomial.o: binomial.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

binomial: $(OBJS) main.cpp
	$(CC) -o $@ $(CFLAGS) $^ 
