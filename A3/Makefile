CC 			 := g++
CFLAGS 		 := -Wall -std=c++11

OBJS 		 := customErrorClass.o LLRB.o
DEPS 		 := customErrorClass.h LLRB.h

.PHONY: clean all

all: LLRB

clean:
	rm $(OBJS) LLRB

customErrorClass.o: customErrorClass.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

customErrorHandling.o: customErrorHandling.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

LLRB.o: LLRB.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

LLRB: $(OBJS) mainLLRB.cpp
	$(CC) -o $@ $(CFLAGS) $^ 
