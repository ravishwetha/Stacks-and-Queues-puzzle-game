//Stacks and Queues
//Copyright © 2016 TeamSQ. All rights reserved.

//Ball.hpp

#ifndef Ball_hpp
#define Ball_hpp

#include "Globals.hpp"

class Ball {
private:
    float x, y;
    float vx, vy;
    float radius;
    float dia;
    
    sf::Color color;
    sf::String label;
    
public:
    bool isActive;
    bool isMoving;
    bool isOnScreen;
    
    Ball(float x, float y, float vx, float vy, float radius, sf::Color color, sf::String label);
    
    bool checkOnScreen();
    void update(bool status);
    void draw();
    
};

#endif /* Ball_hpp */
