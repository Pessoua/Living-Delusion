run:
	gcc -c -O2 *.c	
	$(MAKE) -C art full
	$(MAKE) -C ext full
	$(MAKE) -C games full
	$(MAKE) -C local full
	$(MAKE) -C nina full
	$(MAKE) -C os full
	$(MAKE) -C save full
	$(MAKE) -C .. obj
	gcc -shared -o LD_LIB.dll *.o
	move /Y LD_LIB.dll ..

art:
	$(MAKE) -C art full

ext: 
	$(MAKE) -C ext full

extras: extra!ld.c
	gcc -c -O2 extras!ld.c

games: 
	$(MAKE) -C games full

local:
	$(MAKE) -C local full

nina: nina!ld.c
	$(MAKE) -C nina full

os:
	$(MAKE) -C os full

osmanip:
	$(MAKE) -C os full

save:
	$(MAKE) -C save full

style: style!ld.c
	gcc -c -O2 style!ld.c 

sys: sys!ld.c
	gcc -c -O2 sys!ld.c

dll:
	gcc -shared -o LD_LIB.dll *.o
	move /Y LD_LIB.dll ..

clean:
	del /s *.o
