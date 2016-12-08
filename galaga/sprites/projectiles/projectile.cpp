// creep.cpp
// functions for the Creep Class
#include "../../../gfxnew.h"

#include "../sprite.h"

#include "projectile.h"


//CONSTRUCTOR
Projectile::Projectile() : Sprite() {}
Projectile::Projectile(int x, int y, int w, int h, bool t ) : Sprite(x,y,w,h) {
  type = t;
}
//DESTRUCTOR
Projectile::~Projectile(){}

//UTILITY
// draws missile in appropriate direction for TYPE
//  TYPE:
//   true - player-fired
//   false - creep-fired
void Projectile::draw(){
  int x = this->getXpos();
  int y = this->getYpos();
  XPoint points[] = {
    {x-1,y-7},{x-1,y-3},{x-3,y-3},
    {x-3,y+1},{x-1,y+1},
    {x-1,y+7},{x+1,y+7},
    {x+1,y+1},{x+3,y+1},
    {x+3,y-3},{x+1,y-3},
    (x+1,y-7)
  };
  XPoint apoints[] = {
    {x-1,y+7},{x-1,y+3},{x-3,y+3},
    {x-3,y-1},{x-1,y-1},
    {x-1,y-7},

    {x+1,y-7},
    {x+1,y-1},{x+3,y-1},
    {x+3,y+3},{x+1,y+3},
    (x+1,y+7)
  };
  gfx_color(0,0,255);
  if (type){
    gfx_fill_polygon(points,11);
  } else {
    gfx_fill_polygon(apoints,11);
  }

  gfx_flush();
}
