CPPFLAGS=-Wall -Werror -std=gnu++98 -pedantic -ggdb3

circles: main.cpp points
	g++ -c main.cpp $(CPPFLAGS) -o circles

points:
	g++ -c point.cpp $(CPPFLAGS)

clean:
	rm -f circles points \#* *~ *.o
