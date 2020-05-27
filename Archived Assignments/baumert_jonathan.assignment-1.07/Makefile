rlg327: rlg327.o utils.o dice.o description.o

rlg327.o:rlg327.cpp
	g++ -Wall -Werror -ggdb3 -funroll-loops rlg327.cpp -c

utils.o:utils.cpp utils.h
	g++ -Wall -Werror -ggdb3 -funroll-loops utils.cpp -c

dice.o:dice.cpp
	g++ -Wall -Werror -ggdb3 -funroll-loops dice.cpp -c

description.o:description.cpp description.h
	g++ -Wall -Werror -ggdb3 -funroll-loops description.cpp -c

clean:
	rm -f rlg327 *~ *.o
