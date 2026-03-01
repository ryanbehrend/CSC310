INCLUDE_DIRS := Includes
CC 			 := g++
CFLAGS 		 := -I$(INCLUDE_DIRS)

OBJS 		 := customErrorClass.o customErrorHandling.o bst.o
DEPS 		 := ${INCLUDE_DIRS}/customErrorClass.h ../bst.h

.PHONY: clean all

all: bst

clean:
	rm $(OBJS) bst

customErrorClass.o: customErrorClass.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

customErrorHandling.o: customErrorHandling.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

bst.o: ../bst.cpp ${DEPS}
	$(CC) -c -o $@ $(CFLAGS) $<

bst: $(OBJS) ../mainbst.cpp
	$(CC) -o $@ $(CFLAGS) $^ 
