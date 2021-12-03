CFLAGS=-std=gnu++98 -pedantic -Wall -Werror -ggdb3

cyoa-step4: cyoa-step4.cpp cyoa.o
	g++ $(CFLAGS) -o cyoa-step4 cyoa.cpp cyoa-step4.cpp

cyoa.o: cyoa.h

.PHONY: clean
clean:
	rm -f *~ cyoa-step4
