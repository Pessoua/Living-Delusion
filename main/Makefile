run:
	$(MAKE) -C . link 
	.\LD -d

link:
	gcc -c LD.c -lstdc++
	gcc LD.o -o LD -L. -lLD_LIB

obj:
	gcc -c -O2 LivingDelusion.c
	move /Y LivingDelusion.o libs/

obj-dll:
	$(MAKE) -C . obj
	$(MAKE) -C libs/ dll

test:
	gcc -c LDtest.c -lstdc++
	gcc LDtest.o -o test -L. -lLD_LIB
	.\test
