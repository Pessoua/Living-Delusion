run:
	gcc -c LD.c -lstdc++ 					
	gcc LD.o -o LD -L. -lLD_LIB 
	.\LD

obj:
	gcc -c -O2 LivingDelusion.c
	move /Y LivingDelusion.o libs/

obj-dll:
	$(MAKE) -C . obj
	$(MAKE) -C libs/ dll
