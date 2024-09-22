DOTHAT = gcc -c -O2
MOVE = move /Y *.o ..

full:
	$(DOTHAT) *.c
	$(MOVE)	

test:
	$(DOTHAT) *.c

animal: animal!ld.c
	$(DOTHAT) animal!ld.c

crop: crop!ld.c
	$(DOTHAT) crop!ld.c

fish: fish!ld.c
	$(DOTHAT) fish!ld.c

tree: tree!ld.c
	$(DOTHAT) tree!ld.c

dll:
	$(DOTHAT) *.c
	$(MOVE)	
	$(MAKE) -C .. dll

clean:
	del /s *o
