#ifndef MAP_HPP_INCLUDED
#define MAP_HPP_INCLUDED
#include "brick.h"

const int VIDE = -1;

const int ROW_COUNT = 20;
const int COL_COUNT = 10;

class map{
//private:
public:
    int status[ROW_COUNT][COL_COUNT];
    brick brick_p;
    brick brick_next;
    int brickCenter[2]={0,0};

    map();
    void show();
    bool nextBrick();
    bool down();
    bool left();
    bool right();
    bool rotation();
    int removeRaw();
    int getState(int x,int y){return status[x][y];}
    int brick_x(int i) {return brickCenter[0]+bricks[brick_p.code][brick_p.direction][i][0];}
    int brick_y(int i) {return brickCenter[1]+bricks[brick_p.code][brick_p.direction][i][1];}
    int brickNext_x(int i) {return bricks[brick_next.code][brick_next.direction][i][0];}
    int brickNext_y(int i) {return bricks[brick_next.code][brick_next.direction][i][1];}
};

map::map(){
    std::memset(status,VIDE,sizeof(status));
    brickCenter[1] = 5;
}

void map::show(){
    for (int i=0;i<ROW_COUNT;i++){
        for (int j=0;j<COL_COUNT;j++)
            std::cout << status[i][j];
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

bool map::down(){
    for (int i=0;i<4;i++){
        if(status[1+brick_x(i)][brick_y(i)]!=VIDE
           ||1+brick_x(i)>=ROW_COUNT)
        return false;
    }
    brickCenter[0]++;
    return true;
}

bool map::left(){
    for (int i=0;i<4;i++){
        if(status[brick_x(i)][-1+brick_y(i)]!=VIDE
           ||brick_y(i)-1<0)
        return false;
    }
    brickCenter[1]--;
    return true;
}

bool map::right(){
    for (int i=0;i<4;i++){
        if(status[brick_x(i)][1+brick_y(i)]!=VIDE
           ||brick_y(i)+1>=COL_COUNT)
        return false;
    }
    brickCenter[1]++;
    return true;
}

bool map::rotation(){
    int statu_next;
    if (brick_p.direction==3) statu_next=0;
    else statu_next=1+brick_p.direction;

    for (int i=0;i<4;i++){
        if(status[brickCenter[0]+bricks[brick_p.code][statu_next][i][0]][brickCenter[1]+bricks[brick_p.code][statu_next][i][1]]!=VIDE
           ||brickCenter[1]+bricks[brick_p.code][statu_next][i][1]>=COL_COUNT
           ||brickCenter[1]+bricks[brick_p.code][statu_next][i][1]<0
           ||brickCenter[0]+bricks[brick_p.code][statu_next][i][0]>=ROW_COUNT
           ||brickCenter[0]+bricks[brick_p.code][statu_next][i][0]<0)
        return false;
    }

    brick_p.direction=statu_next;
    return true;
}
int map::removeRaw(){
    int rawCount=0;
    for (int i = ROW_COUNT-1; i >= 0; i--){
        int x = 0;
        for (int j = 0; j < COL_COUNT; j++)
            if (status[i][j]!=VIDE) x++;
        if (x == COL_COUNT){
            rawCount++;
            for (int m = i; m >= 0; m--)
                for (int n = 0; n < COL_COUNT; n++)
                    if (m==0)status[m][n]=VIDE;
                    else
                    status[m][n] = status[m - 1][n];
            ++i;
        }
    }
    return rawCount;
}

bool map::nextBrick(){
    for (int i=0;i<4;i++)
        status[brick_x(i)][brick_y(i)]=brick_p.code;
    brickCenter[1] = 5;
    brickCenter[0] = 0;
    brick_p=brick_next;
    brick_next.newBrick();
    for (int i=0;i<4;i++){
        if(status[brick_x(i)][brick_y(i)]!=VIDE)
        {
            return false;
        }
    }
    return true;
}

#endif // MAP_HPP_INCLUDED
