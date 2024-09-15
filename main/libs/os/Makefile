full:
	gcc -c -O2 *.c
	move /Y *.o ..

test:
	gcc -c -O2 *.c

linux: linux!ld.c
	gcc -c -O2 linux!ld.c

wind: windows!ld.c
	gcc -c -O2 windows!ld.c

dll:
	gcc -c -O2 *.c
	move /Y *.o ..
	$(MAKE) -C .. dll

clean:
	del /s *.o
