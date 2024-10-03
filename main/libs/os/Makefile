DOTHAT = gcc -c -O2 -Wall -Wextra
MOVE = move /Y *.o ..

full:
	$(DOTHAT) *.c
	$(MOVE)

test:
	$(DOTHAT) *.c

linux: linux!ld.c
	$(DOTHAT) linux!ld.c

wind: windows!ld.c
	$(DOTHAT) windows!ld.c

dll:
	$(DOTHAT) *.c
	$(MOVE)
	$(MAKE) -C .. dll

clean:
	del /s *.o
