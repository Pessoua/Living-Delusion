full:
	gcc -c -O2 *.c
	move /Y *.o ..

test:
	gcc -c -O2 *.c

table: table!ld.c
	gcc -c -O2 table!ld.c

ascii: ascii!ld.c
	gcc -c -O2 table!ld.c

tricks: tricks!ld.c
	gcc -c -O2 tricks!ld.c

dll:
	gcc -c -O2 *.c
	move /Y *.o ..
	$(MAKE) -C .. dll

clean:
	del /s *.o
