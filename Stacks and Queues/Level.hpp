//Stacks and Queues
//Copyright © 2016 TeamSQ. All rights reserved.

//Level.hpp

#ifndef Level_hpp
#define Level_hpp

#include "tStack.hpp"
#include "tQueue.hpp"

class Level {
private:
    float inTubePosX;
    float inTubePosY;
    bool pathStored;
    float inVerticalXdot;
    float inVerticalYdot;
    
public:
    int num;
    int status; // -1 for loss, 0 for ongoing, 1 for win
    std::vector<string> winOrder;
    string levelBarLabel;
    
    bool isActive;
    bool ballsInitiated; //timed entry of balls only happen once
    
    //objects in level
    clock_t ballClock;
    std::vector<Ball> balls;
    int selectedBall = 0;
    std::vector<tStack> stacks;
    std::vector<tQueue> queues;
    
    sf::Color lineColor = sf::Color::Yellow;
    sf::Color lineOutlineColor = sf::Color::Black;
    
    Level(int num, std::vector<string> winOrder);
    
    //getters
    float getInTubePositionX();
    float getInTubePositionY();
    float getBallVX();
    float getBallPeriod();
    float getBallRadius();
    
    //methods
    float abs(float num);
    float min(float a, float b);
    int min(int a, int b);
    void startBallClock();
    float getInterval();
    int prevBall(); /* Returns index of new selected ball. */
    int nextBall(); /* Returns index of new selected ball. */
    
    /* Checks if any ball is at the mouth of a stack or a queue. Then automtically pushes it in. It then returns the index of the stack or queue the ball has been pushed in. (Negative index-1) for stack and (Positive index+1) for queue, if nothing happened, 0 is returned. Eg. if a ball is pushed into a queue of index 3 (4th position) in the Level's queue vector, the integer 4 is returned. If it is the stack of index 2 (3rd position), then the integer -3 is returned.
     */
    int checkForSPush();
    int checkForQPush();
    
    /* Checks if a stack or queue has been clicked on and triggers the appropriate tStack method depending on whether it was a right or left mouse button click. Left button for pop() and right button for top(). Also modifies the Ball class boolean flags, isPushed and isTopped accordingly.
    */
    void checkForSQSelect(float x, float y, string action);
    
    /* Checks if the ball that just exited satisfied the winOrder condition. Returns -1 for loss, 0 for level not over yet, 1 for win.
    */
    int checkForWin();
    
    void updateLevel();
    string makeLevelBarLabel();
    void drawLevelBar();
    void drawInTube();
    void drawOutTube();
    void drawStandardPath();
    void drawQueuePath();
    void drawStackPath();
    void drawLevel();
    void clearLevel();
};

#endif /* Level_hpp */
