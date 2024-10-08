DOTHAT = gcc -c -O2 -Wall -Wextra
MOVE = move /Y *.o ..

full:
	$(DOTHAT) *.c
	$(MOVE)

test:
	$(DOTHAT) *.c

make: make!ld.c
	$(DOTHAT) make!ld.c

read: read!ld.c
	$(DOTHAT) read!ld.c

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
