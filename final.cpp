/*
PACMAN
final.cpp
main function of pacman program
 loads high scrore, board, and sprites, then lets game run itself

Douglas Smith
12-5-16
*/

#include <iostream>

#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "galaga/sprites/sprite.h"
#include "galaga/sprites/ship/ship.h"
#include "galaga/sprites/creeps/creep.h"

#include "galaga/sprites/projectiles/projectile.h"


#include "gfxnew.h"

using namespace std;

int loadHighscore( string );
void saveHighScore( int, string );

void drawBoard(int,int,int,Ship&, vector<Creep>&);

const int xMax=600;
const int yMax=600;

int main(){
  int highscore = loadHighscore("scores/highscore.txt");
  int score=0,lives=3;
  char in;

  //Project proj(400,400,3,6);

  Ship player(xMax/2,yMax-20,40,20);
  cout << "SHIP\n";
  vector<Creep> enemies;
  Creep bug(100,100, 20,20,"butterfly");
  cout << "CREEP\n";
  enemies.insert(enemies.end(),bug);
  cout << "OPEN\n";
  gfx_open(xMax,yMax,"GALAGA");
  drawBoard(lives,score,highscore,player,enemies);

  while(1){
    in=gfx_wait();
    if( in=='Q' ){
      player.move(-1,0);
      drawBoard(lives,score,highscore,player,enemies);
    } else if( in=='S' ){
      player.move(1,0);
      drawBoard(lives,score,highscore,player,enemies);
    } else if(in==' '){
      drawBoard(lives,score,highscore,player,enemies);
    }
  }

  //SAVE active high score before program ends
  saveHighScore(highscore,"scores/highscore.txt");
return 0;
}

//Functrion to draw the board anew
void drawBoard(int lives,int score,int high,Ship& s, vector<Creep>& c){
  //Strings that will be used to display statuses
  gfx_color(255,255,255);
  string liv;
  liv = "Lives: "+to_string(lives);
  string scr;
  scr = "Score: " + to_string(score);
  string max;
  max = "High Score: " + to_string(high);

  gfx_clear();

  gfx_text(0,10,liv.c_str() );
  gfx_text(200,10,scr.c_str() );
  gfx_text(400,10,max.c_str() );

  s.draw();
  for( auto & it : c ){
    it.draw();
  }
}

//Loads the high score from a sored value and returns the integer value of the score
int loadHighscore( string fname ){
  int out = 0;
  ifstream fs;
  fs.open( fname.c_str() );
  string line;
  getline(fs,line);

  out = stoi(line);

  fs.close();
  return out;
}


void saveHighScore( int score, string fname ){
  ofstream fs;
  fs.open( fname.c_str() );
  fs << score;
  fs.close();
}
