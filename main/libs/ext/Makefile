DOTHAT = gcc -c -O2 -Wall -Wextra
MOVE = move /Y *.o ..

full:
	$(DOTHAT) *.c
	$(MOVE)

test:
	$(DOTHAT) *.c

time: time!ld.c
	$(DOTHAT) time!ld.c

inv: inventory!ld.c
	$(DOTHAT) inventory!ld.c

inventory: inventory!ld.c
	$(DOTHAT) inventory!ld.c

set: settings!ld.c
	$(DOTHAT) settings!ld.c

settings: settings!ld.c
	$(DOTHAT) settings!ld.c

start: start!ld.c
	$(DOTHAT) start!ld.c
	
help: help!ld.c
	$(DOTHAT) help!ld.c

dll:
	$(DOTHAT) *.c
	$(MOVE)
	$(MAKE) -C .. dll

mv:
	$(MOVE)

move:
	$(MOVE)

clean:
	del /s *.o
