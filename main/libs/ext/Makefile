full:
	gcc -c -O2 *.c
	move /Y *.o ..

test:
	gcc -c -O2 *.c

time: time!ld.c
	gcc -c -O2 time!ld.c

inv: inventory!ld.c
	gcc -c -O2 inventory!ld.c

inventory: inventory!ld.c
	gcc -c -O2 inventory!ld.c

set: settings!ld.c
	gcc -c -O2 settings!ld.c

settings: settings!ld.c
	gcc -c -O2 settings!ld.c

start: start!ld.c
	gcc -c -O2 start!ld.c
	
help: help!ld.c
	gcc -c -O2 help!ld.c

dll:
	gcc -c -O2 *.c
	move /Y *.o ..
	$(MAKE) -C .. dll

clean:
	del /s *.o
