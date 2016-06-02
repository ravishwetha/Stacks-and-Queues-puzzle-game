//Stacks and Queues
//Copyright © 2016 TeamSQ. All rights reserved.

//Level.hpp

#ifndef Level_hpp
#define Level_hpp

#include "tStack.hpp"

class Level {
private:
    std::vector<float> inTubePositionX;
    std::vector<float> inTubePositionY;
    std::vector<float> ballsPeriod; //balls appear on screen every x seconds
    std::vector<float> ballsVX; //respective vx of balls in a level by level number
    std::vector<float> ballsRadii;
    
public:
    int num;
    bool isActive;
    
    //objects in level
    clock_t ballClock;
    std::vector<Ball> balls;
    std::vector<tStack> stacks;
    
    Level(int num);
    
    //getters
    float getInTubePositionX();
    float getInTubePositionY();
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
