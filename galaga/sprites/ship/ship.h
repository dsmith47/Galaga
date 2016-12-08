// ship.h
// Upgrades on sprite file
#ifndef SHIP_H
#define SHIP_H

#include "../sprite.h"

class Ship : public Sprite{
public:
  Ship();
  Ship(int,int,int,int);
  ~Ship();
  void draw();
  void fireProjectile();
private:

};

#endif
