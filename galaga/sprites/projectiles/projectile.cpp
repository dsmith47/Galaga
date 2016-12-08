// creep.cpp
// functions for the Creep Class
#include "../../../gfxnew.h"

#include "../sprite.h"

#include "projectile.h"


//CONSTRUCTOR
Projectile::Projectile() : Sprite() {}
Projectile::Projectile(int x, int y, int w, int h) : Sprite(x,y,w,h) {}
//DESTRUCTOR
Projectile::~Projectile(){}

//UTILITY
// draws the appropriate enemy by types
void Projectile::draw(){
  XPoint points[] = {

  };

  gfx_color(255,0,0);
  gfx_fill_polygon(points,40);
  gfx_flush();
}
