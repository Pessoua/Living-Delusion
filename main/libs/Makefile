run:
	gcc -c -O2 art!ld.c	
	gcc -c -O2 extras!ld.c 
	gcc -c -O2 games!ld.c 
	gcc -c -O2 nina!ld.c
	gcc -c -O2 osmanip!ld.c
	gcc -c -O2 path!ld.c
	gcc -c -O2 save!ld.c
	gcc -c -O2 style!ld.c 
	gcc -c -O2 sys!ld.c
	gcc -shared -o LD_LIB.dll *.o
	move /Y LD_LIB.dll ..

art:
	gcc -c -O2 art!ld.c

extras:
	gcc -c -O2 extras!ld.c

games:
	gcc -c -O2 games!ld.c 

nina:
	gcc -c -O2 nina!ld.c

os:
	gcc -c -O2 osmanip!ld.c

osmanip:
	gcc -c -O2 osmanip!ld.c

path:
	gcc -c -O2 path!ld.c

save:
	gcc -c -O2 save!ld.c

style:
	gcc -c -O2 style!ld.c 

sys:
	gcc -c -O2 sys!ld.c

dll:
	gcc -shared -o LD_LIB.dll *.o
	move /Y LD_LIB.dll ..
