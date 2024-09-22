DOTHAT = gcc -c -O2
MOVE = move /Y *.o ..

full:
	$(DOTHAT) *.c
	$(MOVE)

test:
	$(DOTHAT) *.c

table: table!ld.c
	$(DOTHAT) table!ld.c

ascii: ascii!ld.c
	$(DOTHAT) table!ld.c

tricks: tricks!ld.c
	$(DOTHAT) tricks!ld.c

dll:
	$(DOTHAT) *.c
	$(MOVE)
	$(MAKE) -C .. dll

clean:
	del /s *.o
