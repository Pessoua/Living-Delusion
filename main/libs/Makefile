DOTHAT = gcc -c -O2
FILE = $(MAKE) -C
LINK = gcc -shared -o LD_LIB.dll *.o
MOVE = move /Y LD_LIB.dll ..

run:
	$(DOTHAT) *.c	
	$(FILE) art full
	$(FILE) ext full
	$(FILE) games full
	$(FILE) local full
	$(FILE) nina full
	$(FILE) os full
	$(FILE) save full
	$(FILE) .. obj
	$(LINK)
	$(MOVE)

art:
	$(FILE) art full

ext: 
	$(FILE) ext full

extras: extras!ld.c
	$(DOTHAT) extras!ld.c

games: 
	$(FILE) games full

local:
	$(FILE) local full

nina: nina!ld.c
	$(FILE) nina full

os:
	$(FILE) os full

osmanip:
	$(FILE) os full

save:
	$(FILE) save full

style: style!ld.c
	$(DOTHAT) style!ld.c 

sys: sys!ld.c
	$(DOTHAT) sys!ld.c

dll:
	$(LINK)
	$(MOVE)

clean:
	del /s *.o
