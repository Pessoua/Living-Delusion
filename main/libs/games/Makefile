full:
	gcc -c -O2 *.c
	move /Y *.o ..

test:
	gcc -c -O2 *.c

animal: animal!ld.c
	gcc -c -O2 animal!ld.c

crop: crop!ld.c
	gcc -c -O2 crop!ld.c

fish: fish!ld.c
	gcc -c -O2 fish!ld.c

tree: tree!ld.c
	gcc -c -O2 tree!ld.c

dll:
	gcc -c -O2 *.c
	move /Y *.o ..
	$(MAKE) -C .. dll

clean:
	del /s *o
