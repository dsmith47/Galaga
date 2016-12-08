// creep.h

#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "../sprite.h"
#include "projectile.h"
#include <string>

class Projectile : public Sprite{
public:
  Projectile();
  Projectile(int,int,int,int,bool);
  ~Projectile();
  void draw();
private:
  bool type; // player-fired vs. creep-fired
};

#endif
