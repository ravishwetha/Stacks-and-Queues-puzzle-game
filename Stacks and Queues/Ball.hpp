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
    
    sf::Color selectColor;
    sf::Color color;
    sf::String label;
    
public:
    int num;
    
    bool isActive;
    bool isMoving;
    bool isOnScreen;
    bool isSelected;
    
    //1 = left, 2 = up, 3 = down
    int currDirection;
    int nextDirection;
    
    Ball(int num, float x, float y, float vx, float vy, float radius, sf::Color color, sf::String label);
    
    bool checkOnScreen();
    void changeDirection(int nextDirection);
    void move();
    void select();
    void deselect();
    void update(bool status);
    void draw();
};

#endif /* Ball_hpp */
