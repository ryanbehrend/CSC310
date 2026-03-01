CC 			 := g++
CFLAGS 		 := -Wall -std=c++11

OBJS 		 := customErrorClass.o dsw.o
DEPS 		 := customErrorClass.h dsw.h

.PHONY: clean all

all: dsw

clean:
	rm $(OBJS) dsw

customErrorClass.o: customErrorClass.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

customErrorHandling.o: customErrorHandling.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

dsw.o: dsw.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

dsw: $(OBJS) main.cpp
	$(CC) -o $@ $(CFLAGS) $^ 
