run:
	gcc -c -O2 *.c
	move /Y *.o ../main/libs
	$(MAKE) -C ../main/libs dll

tests: tests!ld.c
	gcc -c tests!ld.c

dll:
	move /Y *.o ../main/libs
	$(MAKE) -C ../main/libs dll
