// ship.cpp
// functions for Ship Class

#include "../../../gfxnew.h"

#include "../sprite.h"
#include "../sprite.cpp"
#include "../projectiles/projectile.h"
#include "ship.h"

//CONSTRUCTOR
Ship::Ship() : Sprite() {}
Ship::Ship(int x, int y, int w, int h) : Sprite(x,y,w,h) {}
//DESTRUCTOR
Ship::~Ship(){}

//UTILITY
//Creates a projectile object that travels up the screen to impact a creep
Projectile Ship::fireProjectile(){
  int x = this->getXpos();
  int y = this->getYpos();
  Projectile p(x,(y-30),3,6,true);
  return p;
}
// draws the image
void Ship::draw(){
  int x = this->getXpos();
  int y = this->getYpos();

  XPoint points[] = {
    {x-15,y}, {x-15,y-7}, {x-13,y-7}, {x-13, y-4},
    {x-11, y-4},
    {x-11, y-6}, {x-9,y-6},
    {x-9, y-10}, {x-7, y-10},
    {x-7, y-8}, {x-5, y-8},
    {x-5, y-12}, {x-3, y-12},
    {x-3, y-16}, {x-1, y-16},
    {x-1, y-20}, {x+1, y-20}, //
    {x+1, y-16}, {x+3,y-16},
    {x+3, y-12}, {x+5, y-12},
    {x+5, y-8}, {x+7, y-8},
    {x+7, y-10}, {x+9,y-10},
    {x+9, y-6}, {x+11, y-6},
    {x+11,y-4},
    {x+13,y-4},{x+13,y-7},{x+15,y-7},{x+15,y}
  };
  gfx_color(255,255,255);
  gfx_fill_polygon(points,32);
  gfx_flush();
}
