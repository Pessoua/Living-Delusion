DOTHAT = gcc -c -O2
MOVE = move /Y *.o ..

full:
	$(DOTHAT) *.c
	$(MOVE)

test:
	$(DOTHAT) *.c

file: file!ld.c
	$(DOTHAT) file!ld.c

make: make!ld.c
	$(DOTHAT) make!ld.c

exit: exit!ld.c
	$(DOTHAT) exit!ld.c

check: check!ld.c
	$(DOTHAT) check!ld.c

path: path!ld.c
	$(DOTHAT) path!ld.c

dll:
	$(DOTHAT) *.c
	$(MOVE)
	$(MAKE) -C .. dll

clean:
	del /s *.o
