full:
	gcc -c -O2 *.c
	move /Y *.o ..

test:
	gcc -c -O2 *.c

file: file!ld.c
	gcc -c -O2 file!ld.c

make: make!ld.c
	gcc -c -O2 make!ld.c

exit: exit!ld.c
	gcc -c -O2 exit!ld.c

check: check!ld.c
	gcc -c -O2 check!ld.c

path: path!ld.c
	gcc -c -O2 path!ld.c

dll:
	gcc -c -O2 *.c
	move /Y *.o ..
	$(MAKE) -C .. dll

clean:
	del /s *.o
