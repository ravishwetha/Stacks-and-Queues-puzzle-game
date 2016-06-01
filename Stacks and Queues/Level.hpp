//Stacks and Queues
//Copyright © 2016 TeamSQ. All rights reserved.

//Level.hpp

#ifndef Level_hpp
#define Level_hpp

#include "Ball.hpp"

class Level {
private:
    std::vector<float> ballsPositionX;
    std::vector<float> ballsPositionY;
    std::vector<float> ballsPeriod; //balls appear on screen every x seconds
    std::vector<float> ballsVX; //respective vx of balls in a level by level number
    std::vector<float> ballsRadii;
    
public:
    int num;
    bool isActive;
    
    //objects in level
    clock_t ballClock;
    std::vector<Ball> balls;
    
    Level(int num);
    
    //getters
    float getBallPositionX();
    float getBallPositionY();
    float getBallVX();
    float getBallPeriod();
    float getBallRadius();
    
    //methods
    void startBallClock();
    float getInterval();
    void updateLevel();
    void drawInTube();
    void drawOutTube();
    void drawLevel();
    void clearLevel();
};

#endif /* Level_hpp */
