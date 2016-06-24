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
    std::vector<float> ballsPeriod; /* Balls appear on screen every x seconds. */
    std::vector<float> ballsVX; /* Respective vx of balls in a level by level number. */
    std::vector<float> ballsRadii;
    
    float inTubePosX;
    float inTubePosY;
    bool pathStored;
    
public:
    int num;
    bool isActive;
    
    //objects in level
    clock_t ballClock;
    std::vector<Ball> balls;
    int selectedBall = 0;
    std::vector<tStack> stacks;
    sf::Color lineColor = sf::Color::Yellow;
    sf::Color lineOutlineColor = sf::Color::Black;
    
    Level(int num);
    
    //getters
    float getInTubePositionX();
    float getInTubePositionY();
    float getBallVX();
    float getBallPeriod();
    float getBallRadius();
    
    //methods
    float abs(float num);
    void startBallClock();
    float getInterval();
    int prevBall(); /* Returns index of new selected ball. */
    int nextBall(); /* Returns index of new selected ball. */
    
    /* Checks if any ball is at the mouth of a stack or a queue. Then automtically pushes it in. It then returns the index of the stack or queue the ball has been pushed in. (Negative index-1) for stack and (Positive index+1) for queue, if nothing happened, 0 is returned. Eg. if a ball is pushed into a queue of index 3 (4th position) in the Level's queue vector, the integer 4 is returned. If it is the stack of index 2 (3rd position), then the integer -3 is returned.
     */
    int checkForPush();
    //TODO: test
    void checkForSQSelect(float x, float y, string action);
    //TODO:test
    
    void updateLevel();
    void drawInTube();
    void drawOutTube();
    void drawPath();
    void drawLevel();
    void clearLevel();
};

#endif /* Level_hpp */
