// creep.h

#ifndef CREEP_H
#define CREEP_H

#include "../sprite.h"
#include "projectile.h"
#include <string>

class Projectile : public Sprite{
public:
  Projectile();
  Projectile(int,int,int,int);
  ~Projectile();
  void draw();
private:
};

#endif
