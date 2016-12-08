// creep.h

#ifndef CREEP_H
#define CREEP_H

#include "../sprite.h"
#include "../projectiles/projectile.h"
#include <string>

class Creep : public Sprite{
public:
  Creep();
  Creep(int,int,int,int,std::string);
  ~Creep();
  void draw();
  Projectile fireProjectile();
private:
  std::string type;
};

#endif
