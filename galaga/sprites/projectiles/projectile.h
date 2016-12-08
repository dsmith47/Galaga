// creep.h

#ifndef PROJECTILE_H
#define PROJECTILE_H

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
