rlg327:dungeon.o heap.o rlg327.o  path.o utils.o character.o event.o pc.o npc.o move.o
	gcc dungeon.o heap.o rlg327.o  path.o utils.o character.o event.o pc.o npc.o move.o  -o rlg327 -Wall -Werror -ggdb -lncurses 
	
character.o:character.c character.h heap.h npc.h pc.h dungeon.h
	gcc -ggdb -Wall -Werror character.c -c

dungeon.o: dungeon.c dungeon.h utils.h heap.h event.h
	gcc -ggdb -Wall -Werror dungeon.c -c

event.o:event.c event.h
	gcc -ggdb -Wall -Werror event.c -c

heap.o:heap.c heap.h
	gcc -ggdb -Wall -Werror heap.c -c

move.o:move.c move.h
	gcc -ggdb -Wall -Werror move.c -c

npc.o:npc.c npc.h dungeon.h pc.h move.h character.h path.h event.h move.h
	gcc -ggdb -Wall -Werror npc.c -c	

path.o:path.c path.h dungeon.h
	gcc -ggdb -Wall -Werror path.c -c

pc.o:pc.c pc.h
	gcc -ggdb -Wall -Werror pc.c -c

rlg327.o:rlg327.c dungeon.h pc.h npc.h move.h
	gcc -ggdb -Wall -Werror rlg327.c -c

utils.o:utils.c utils.h
	gcc -ggdb -Wall -Werror utils.c -c

clean:
	rm -f rlg327 *~ *.o

