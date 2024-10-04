CC = gcc
FLAGS = -c -O2 -lstdc++ -Wall -Wextra
LIB = -L. -lLD_LIB

run: LD.c
	$(MAKE) -C . link 
	.\LD -d -i

link: LD.c
	$(CC) $(FLAGS) LD.c 
	$(CC) LD.o -o LD $(LIB)

obj: LivingDelusion.c
	$(CC) $(FLAGS) LivingDelusion.c
	move /Y LivingDelusion.o libs/

obj-dll:
	$(MAKE) -C . obj
	$(MAKE) -C libs/ dll

test: LDtest.c
	$(CC) $(FLAGS) LDtest.c
	$(CC) LDtest.o -o test $(LIB)	
	.\test

test-that:
	$(MAKE) -C libs/save/ dll 
	$(MAKE) test

clean:
	del /q *.o 
