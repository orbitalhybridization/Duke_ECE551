CFLAGS=-std=gnu++98 -pedantic -Wall -Werror -ggdb3

cyoa.o: cyoa.cpp
	g++ $(CFLAGS) cyoa.cpp -c

cyoa-step1: cyoa-step1.cpp cyoa.o
	g++ $(CFLAGS) -o cyoa-step2 cyoa-step1.cpp

.PHONY: clean
clean:
	rm -f *~ cyoa-step1
