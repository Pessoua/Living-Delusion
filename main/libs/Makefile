run:
	gcc -c -O2 *.c	
	$(MAKE) -C art full
	$(MAKE) -C games full
	$(MAKE) -C local full
	$(MAKE) -C nina full
	$(MAKE) -C os full
	$(MAKE) -C save full
	$(MAKE) -C .. obj
	gcc -shared -o LD_LIB.dll *.o
	move /Y LD_LIB.dll ..

art: art!ld.c
	gcc -c -O2 art!ld.c

extras: extra!ld.c
	gcc -c -O2 extras!ld.c

games: games!ld.c
	gcc -c -O2 games!ld.c 

nina: nina!ld.c
	gcc -c -O2 nina!ld.c

os: osmanip!ld.c
	gcc -c -O2 osmanip!ld.c

osmanip: osmanip!ld.c
	gcc -c -O2 osmanip!ld.c

path: path!ld.c
	gcc -c -O2 path!ld.c

save: save!ld.c
	gcc -c -O2 save!ld.c

style: style!ld.c
	gcc -c -O2 style!ld.c 

sys: sys!ld.c
	gcc -c -O2 sys!ld.c

dll:
	gcc -shared -o LD_LIB.dll *.o
	move /Y LD_LIB.dll ..

clean:
	del /s *.o
