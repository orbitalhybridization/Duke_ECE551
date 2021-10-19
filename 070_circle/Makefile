CPPFLAGS=-Wall -Werror -std=gnu++98 -pedantic -ggdb3

circle: main.cpp points
	g++ -c main.cpp $(CPPFLAGS) -o circle

points:
	g++ -c point.cpp $(CPPFLAGS)

clean:
	rm -f circle points \#* *~ *.o
