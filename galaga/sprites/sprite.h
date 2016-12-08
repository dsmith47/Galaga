// sprite.h
// file for any object with capability to move on the screen
#ifndef SPRITE_H
#define SPRITE_H

class Sprite{
public:
  Sprite();
  Sprite(int,int,int,int);
  ~Sprite();

  int getXpos();
  void setXpos(int);

  int getYpos();
  void setYpos(int);

  void setColor(int, int, int);

  void move(int, int);
private:
  int xpos;
  int ypos;
  int color[3];
  int width;
  int height;
};

#endif
