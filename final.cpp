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
#include <ctime>
#include <unistd.h>

#include "galaga/sprites/sprite.h"
#include "galaga/sprites/ship/ship.h"
#include "galaga/sprites/creeps/creep.h"

#include "galaga/sprites/projectiles/projectile.h"


#include "gfxnew.h"

using namespace std;

int loadHighscore( string );
void saveHighScore( int, string );

void drawBoard(int,int,int,Ship&, vector<Creep>&, vector<Projectile>&);
void checkCollisions(vector<Projectile>&,vector<Creep>&);

void hail( vector<Projectile>& );

const int xMax=600;
const int yMax=600;

int main(){
  int highscore = loadHighscore("scores/highscore.txt");
  int score=0,lives=3;
  char in;


  Ship player(xMax/2,yMax-20,40,20);
  vector<Creep> enemies;
  vector<Projectile> projs;
  int fireLag =0;
  bool fireReady = false;

  Creep bug(100,100, 20,20,"butterfly");
  enemies.insert(enemies.end(),bug);
  gfx_open(xMax,yMax,"GALAGA");

  drawBoard(lives,score,highscore,player,enemies,projs);

  while(1){
    usleep(10000);
    if( gfx_event_waiting() ){
      in=gfx_wait();
      if( in=='Q' ){
        player.move(-1,0);
      } else if( in=='S' ){
        player.move(1,0);

      } else if(in==' '){
        if(fireReady){
          fireReady=false;
          fireLag = 0;
          projs.insert( projs.end(), player.fireProjectile() );
        }
      } else if(in=='h'){
        cout << "HAIL\n";
        hail(projs);
      }
    }
    if(!fireReady){
      fireLag++;
      if(fireLag>=30){
        fireReady = true;
      }
    }
    //move all projectiles
    for( int i=0; i<(int)projs.size(); ++i ){
      if( projs[i].getYpos() < 40 ){
        projs.erase( projs.begin()+i );
        --i;
      } else {
        projs[i].move(0,-1);
      }
    }
    //Check collisions with player and all enemies
    checkCollisions( projs,enemies );

    drawBoard(lives,score,highscore,player,enemies,projs);

  }

  //SAVE active high score before program ends
  saveHighScore(highscore,"scores/highscore.txt");
return 0;
}

//Functrion to draw the board anew
void drawBoard(int lives,int score,int high,Ship& s, vector<Creep>& c, vector<Projectile>& p){
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
  for( auto & it : p ){
    it.draw();
  }
}

//Check if object has collided with a projectile. If so, removes them both
void checkCollisions(vector<Projectile>& p,vector<Creep>& c){
  //check each projectile against each creep
  for( int i=0; i<(int)p.size(); ++i ){
    for( int j=0; j<(int)c.size(); ++j ){
      if( ( p[i].getXpos()<c[i].getXpos()+c[i].getWidth()/2 )&&( p[i].getXpos()>c[i].getXpos()-c[i].getWidth()/2 )&&( p[i].getYpos()<c[i].getYpos()+c[i].getHeight()/2 )&&( p[i].getYpos()>c[i].getYpos()-c[i].getHeight()/2 ) ){
        p.erase( p.begin()+i );
        c.erase( c.begin()+j );
        --i;
        --j;
      }
    }
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





//EASTER EGGS///////////////////////////////////////////////////////////////////
//Releases a long line of projectile
Projectile createProjectile(int a){
  Projectile proj(a,yMax-40,3,6);
  return proj;
}

void hail( vector<Projectile>& p ){
  Projectile proj(0,0,3,6);
  for(int i=5;i<xMax;i+=5){
    proj.setXpos(i);
    p.insert(p.end(),createProjectile(i) );
  }
}
