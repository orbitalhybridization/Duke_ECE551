bs:  test-bsearch.cpp bsearch.o function.h
	g++ -o bs -ggdb3 -Wall -Werror -pedantic -std=gnu++11 test-bsearch.cpp

bsearch.o: search.cpp
	g++ -ggdb3 -Wall -Werror -pedantic -std=gnu++11 -c search.cpp

.PHONY: clean

clean:
	rm *~ *.o