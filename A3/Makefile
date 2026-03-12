CC 			 := g++
CFLAGS 		 := -Wall -std=c++11

OBJS 		 := customErrorClass.o rb.o
DEPS 		 := customErrorClass.h rb.h

.PHONY: clean all

all: rb

clean:
	rm $(OBJS) rb

customErrorClass.o: customErrorClass.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

customErrorHandling.o: customErrorHandling.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

dsw.o: rb.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

dsw: $(OBJS) main.cpp
	$(CC) -o $@ $(CFLAGS) $^ 
