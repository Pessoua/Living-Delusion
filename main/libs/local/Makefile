DOTHAT = gcc -c -O2
MOVE = move /Y *.o ..

full:
	$(DOTHAT) *.c	
	$(MOVE)

test:
	$(DOTHAT) *.c

teller: teller!ld.c
	$(DOTHAT) teller!ld.c

center: center!ld.c
	$(DOTHAT) center!ld.c

garden: garden!ld.c
	$(DOTHAT) garden!ld.c

wizard: wizard!ld.c
	$(DOTHAT) wizard!ld.c

library: library!ld.c
	$(DOTHAT) library!ld.c

hotel: hotel!ld.c
	$(DOTHAT) hotel!ld.c

mountain: mountain!ld.c
	$(DOTHAT) mountain!ld.c

key: keys!ld.c
	$(DOTHAT) keys!ld.c

special: special!ld.c
	$(DOTHAT) special!ld.c

dll:
	$(DOTHAT) *.c
	$(MOVE)
	$(MAKE) -C .. dll

clean:
	del /s *.o	
