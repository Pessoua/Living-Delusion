full:
	gcc -c -O2 *.c
	move /Y *.o ..

test:
	gcc -c -O2 *.c

teller: teller!ld.c
	gcc -c -O2 teller!ld.c

center: center!ld.c
	gcc -c -O2 center!ld.c

garden: garden!ld.c
	gcc -c -O2 garden!ld.c

wizard: wizard!ld.c
	gcc -c -O2 wizard!ld.c

library: library!ld.c
	gcc -c -O2 library!ld.c

hotel: hotel!ld.c
	gcc -c -O2 hotel!ld.c

mountain: mountain!ld.c
	gcc -c -O2 mountain!ld.c

key: keys!ld.c
	gcc -c -O2 keys!ld.c

special: special!ld.c
	gcc -c -O2 special!ld.c

dll:
	gcc -c -O2 *.c
	move /Y *.o ..
	$(MAKE) -C .. dll

clean:
	del /s *.o	
