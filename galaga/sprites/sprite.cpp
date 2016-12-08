//Sprite.cpp
// functions for sprite class, and moving object on the board


#include "sprite.h"
//CONSTRUCTOR
Sprite::Sprite(){}
Sprite::Sprite(int x, int y, int w, int h){
  xpos = x;
  ypos = y;
  width = w;
  height = h;
}

//DESTRUCTOR
Sprite::~Sprite(){}

//Getters and setters
//returns x position
int Sprite::getXpos(){
  return xpos;
}
//Changes x position
void Sprite::setXpos(int x){
  xpos = x;
}
//returns y position
int Sprite::getYpos(){
  return ypos;
}
//Changes y position
void Sprite::setYpos(int y){
  ypos = y;
}

void Sprite::setColor(int r, int g, int b){
  color[0] = r;
  color[1] = g;
  color[2] = b;
}

//UTILITY
void Sprite::move(int dx, int dy){
  xpos += dx;
  if( xpos < 20 ){
    xpos = 20;
  } else if ( xpos > 600 -20 ){
    xpos = 600 - 20;
  }
  ypos += dy;
  if( ypos < 20 ){
    ypos = 20;
  } else if ( ypos > 600 -20 ){
    ypos = 600 - 20;
  }
}
