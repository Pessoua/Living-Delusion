full:
	gcc -c -O2 *.c
	move /Y *.o ..

test:
	gcc -c -O2 *.c

make: make!ld.c
	gcc -c -O2 make!ld.c

read: read!ld.c
	gcc -c -O2 read!ld.c

dll:
	gcc -c -O2 *.c
	move /Y *.o ..
	$(MAKE) -C .. dll

clean:
	del /s *.o
