// creep.cpp
// functions for the Creep Class
#include "../../../gfxnew.h"

#include "../sprite.h"
#include "../projectiles/projectile.h"

#include "creep.h"


void drawButterfly(int,int);

//CONSTRUCTOR
Creep::Creep() : Sprite() {}
Creep::Creep(int x, int y, int w, int h, std::string t) : Sprite(x,y,w,h) {
  type = t;
}
//DESTRUCTOR
Creep::~Creep(){}

//UTILITY
//Creates a projectile object
Projectile Creep::fireProjectile(){
  int x = this->getXpos();
  int y = this->getYpos();
  Projectile p(x+(2*this->getWidth()/3),(y+30),3,6,false);
  return p;
}
// draws the appropriate enemy by types
void Creep::draw(){
  if ( type == "butterfly" ){
    drawButterfly(this->getXpos(),this->getYpos());
  }
}




//ACTUAL DARWING FUNCTIONS//////////////////////////////////////////////////////
void drawButterfly(int x, int y){

  XPoint points[] = {
    {x-7,y-10}, {x-9,y-10},{x-9,y-8},{x-13,y-8},
    {x-13,y-2},{x-11,y-2},
    {x-11,y},{x-9,y},
    {x-9,y+2},{x-13,y+2},
    {x-13,y+4},{x-15,y+4},
    {x-15,y+6}, {x-13,y+6},
    {x-13,y+8},{x-9,y+8},
    {x-9,y+10},{x-7,y+10},

    {x-7,y+6}, {x+7,y+6},

    {x+7,y+10},{x+9,y+10},
    {x+9,y+8},{x+13,y+8},
    {x+13,y+6},{x+15,y+6},
    {x+15,y+4},{x+13,y+4},
    {x+13,y+2},{y+9,y+2},
    {x+9,y},{x+11,y},
    {x+11,y-2},{x+13,y-2},
    {x+13,y-8},{x+9,y-8},
    {x+9,y-10},{x+7,y-10},
    {x+7,y-2},{x-7,y-2}

  };

  gfx_color(255,0,0);
  gfx_fill_polygon(points,40);
  gfx_flush();
}
