#ifndef PLAYER_H
#define PLAYER_H
#include <cstring>
#include "map.hpp"

int scores[4]={40,100,300,1200};
int levelBoundary[9]={400,1200,2400,4000,6000,8400,11200,14400,18000};
class player{
//private:
public:
    map m;
    bool endOfGame=false;
    int level=0;
    int score=0;

    player();
    void show(){m.show();}
    bool down(){return m.down();}
    bool left(){return m.left();}
    bool right(){return m.right();}
    bool rotation(){return m.rotation();}
    void removeRow();
    void nextBlock();
    int getState(int x,int y){return m.getState(x,y);};
    int getBlockCode(){return m.brick_p.code;}
    int getNextBlockCode(){return m.brick_next.code;}
    int getBlockPosition_x(int i){return m.brick_x(i);}
    int getBlockPosition_y(int i){return m.brick_y(i);}
    int getNextBlockPosition_x(int i){return m.brickNext_x(i);}
    int getNextBlockPosition_y(int i){return m.brickNext_y(i);}

};

player::player(){
    this->level=0;
    this->score=0;
}

void player::removeRow(){
    int rawCount=m.removeRaw();
    if (rawCount) score+=(scores[rawCount-1])*(level+1);
}

void player::nextBlock(){
    if (score>=levelBoundary[level]) level++;
    if (!m.nextBrick()){
        endOfGame=true;
    }
}
#endif // MAP_HPP_INCLUDED
