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
    bool isPushed;
    bool isTopped;
    bool isSelected;
    
    //1 = left, 2 = up, 3 = down
    int currDirection;
    int nextDirection;
    
    Ball(int num, float x, float y, float vx, float vy, float radius, sf::Color color, sf::String label);
    
    //getters
    float getX();
    float getY();
    float getRadius();
    
    bool checkOnScreen();
    /* Checks if next available path junction allows the ball to move in the direction that the player wishes. 
     */
    bool onPath(float x, float y);
    int searchPath(float x, float y);
    /* When the ball is about to derail off the path, this function is automatically called and returns the next the appropriate direction to move.
     */
    void changeDirection(int nextDirection);
    void select();
    void deselect();
    //TODO: test
    void ballOut(); //moves ball out and makes stack and queue related bools default
    //TODO: test
    //TODO: make more efficient?
    void move();
    //TODO: make more efficient?
    void update(bool status);
    void draw();
};

#endif /* Ball_hpp */
