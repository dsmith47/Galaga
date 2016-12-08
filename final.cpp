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

void drawBoard(int,int,int,Ship&, vector<Creep>&, vector<Projectile>&, vector<Projectile>&);
void checkCollisions(vector<Projectile>&,vector<Creep>&);
bool checkDeath(vector<Projectile>&, Ship&);

Projectile createProjectile(int);
Creep createCreep(int,int,int,int, string);

void hail( vector<Projectile>& );
int random( int,int );

const int xMax=600;
const int yMax=600;

int main(){
  int highscore = loadHighscore("scores/highscore.txt");
  int score=0,lives=3;
  char in;


  Ship player(xMax/2,yMax-20,40,20);
  vector<Creep> enemies;
  vector<Projectile> playerProjs, enemyProjs;
  int fireLag =0;
  bool fireReady = false;
  int creepWait=0;

  Creep bug = createCreep(0,100, 20,20,"butterfly");
  for(int i=60; i<xMax-60; i+=60){
    bug = createCreep(i,100, 20,20,"butterfly");
    enemies.insert(enemies.end(),bug);
  }
  gfx_open(xMax,yMax,"GALAGA");

  drawBoard(lives,score,highscore,player,enemies,playerProjs,enemyProjs);

  while(1){
    usleep(20000);
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
          playerProjs.insert( playerProjs.end(), player.fireProjectile() );
        }
      } else if(in=='h'){
        cout << "HAIL\n";
        hail(playerProjs);
      }
    }
    //Timer between player shots
    if(!fireReady){
      fireLag++;
      if(fireLag>=30){
        fireReady = true;
      }
    }
    //timer to check random creep firing
    if( creepWait > 250){
      creepWait = random( 0,enemies.size() );
      cout << "CREEP: " << creepWait << "\n";
      enemyProjs.insert(enemyProjs.end(), enemies[creepWait].fireProjectile());
      creepWait = 0;
    } else {
      ++creepWait;
    }
    //move all projectiles
    for( int i=0; i<(int)playerProjs.size(); ++i ){
      if( playerProjs[i].getYpos() < 40 ){
        playerProjs.erase( playerProjs.begin()+i );
        --i;
      } else {
        playerProjs[i].move(0,-1);
      }
    }
    for( int i=0; i<(int)enemyProjs.size(); ++i ){
      if( enemyProjs[i].getYpos() > yMax-30 ){
        enemyProjs.erase( enemyProjs.begin()+i );
        --i;
      } else {
        enemyProjs[i].move(0,1);
      }
    }
    //Check collisions with projectiles for player and all enemies
    checkCollisions( playerProjs,enemies );
    if( checkDeath( enemyProjs, player ) ) {
      cout << "PLAYER DEATH\n";
      lives -= 1;
      if( lives < 0 ){
        break;
      }
      player.setXpos( xMax / 2 );
    }
    //END THE GAME IF THERE ARE NO CREEP LEFT
    if( enemies.size() <= 0 ){
      break;
    }
    drawBoard(lives,score,highscore,player,enemies,playerProjs,enemyProjs);

  }

  //SAVE active high score before program ends
  saveHighScore(highscore,"scores/highscore.txt");
return 0;
}

//Functrion to draw the board anew
void drawBoard(int lives,int score,int high,Ship& s, vector<Creep>& c, vector<Projectile>& p1, vector<Projectile>& p2){
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
  for( auto & it : p1 ){
    it.draw();
  }
  for( auto & it : p2 ){
    it.draw();
  }
}

//Check if object has collided with a projectile. If so, removes them both
void checkCollisions(vector<Projectile>& p,vector<Creep>& c){
  //check each projectile against each creep
  for( int i=0; i<(int)p.size(); ++i ){
    for( int j=0; j<(int)c.size(); ++j ){
      if( ( p[i].getXpos()<c[j].getXpos()+c[j].getWidth()/2 )&&( p[i].getXpos()>c[j].getXpos()-c[j].getWidth()/2 )&&( p[i].getYpos()<c[j].getYpos()+c[j].getHeight()/2 )&&( p[i].getYpos()>c[j].getYpos()-c[j].getHeight()/2 ) ){
        p.erase( p.begin()+i );
        c.erase( c.begin()+j );
        --i;
        --j;
      }
    }
  }

}

bool checkDeath(vector<Projectile>& c, Ship& p){
  for( int i=0; i<(int)c.size(); ++i ){
    if( ( c[i].getXpos()<p.getXpos()+p.getWidth()/2 )&&( c[i].getXpos()>p.getXpos()-p.getWidth()/2 )&&( c[i].getYpos()<p.getYpos()+p.getHeight()/2 )&&( c[i].getYpos()>p.getYpos()-p.getHeight()/2 ) ){
      return true;
    }
  }
  return false;
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

//RN-Gesus
//Returns a random number between MIN and MAX
int random(int min, int max){
  cout << "MAX: " << max << "\nMIN: "<< min <<"\n";
  int ran = ( std::rand() % (max-min+1) ) + min;
  cout << "RAND: " << ran << "\n";
  return ran;
}

//Creates a creep
Creep createCreep(int x, int y, int w, int h, string t){
  Creep c(x,y,w,h,t);
  return c;
}
//Releases a long line of projectile
Projectile createProjectile(int a){
  Projectile proj(a,yMax-40,3,6,true);
  return proj;
}
//EASTER EGGS///////////////////////////////////////////////////////////////////


void hail( vector<Projectile>& p ){
  Projectile proj(0,0,3,6,true);
  for(int i=5;i<xMax;i+=15){
    proj.setXpos(i);
    p.insert(p.end(),createProjectile(i) );
  }
}
