SPRITE = galaga/sprites/
PROJ = galaga/sprites/projectiles/
SHIP = galaga/sprites/ship/
CREEP = galaga/sprites/creeps/

FLAGS = -std=c++14 -Wall

default:
	make final


clean:
	rm sprite.o proj.o ship.o creep.o


sprite.o: $(SPRITE)sprite.cpp $(SPRITE)sprite.h
	g++ -c $(SPRITE)sprite.cpp -o sprite.o $(FLAGS)


proj.o: $(PROJ)projectile.cpp $(PROJ)projectile.h sprite.o
	g++ -c $(PROJ)projectile.cpp sprite.o -o proj.o $(FLAGS)


ship.o: $(SHIP)ship.cpp $(SHIP)ship.h sprite.o proj.o
	g++ -c $(SHIP)ship.cpp sprite.o proj.o -o ship.o $(FLAGS)


creep.o: $(CREEP)creep.cpp $(CREEP)creep.h sprite.o
	g++ -c $(CREEP)creep.cpp sprite.o -o creep.o $(FLAGS)


final: final.cpp ship.o creep.o proj.o
	g++ final.cpp gfxnew.o ship.o creep.o proj.o -lX11 -o final $(FLAGS)







new:
	g++ new1.cpp gfxnew.o -lX11 -o test
