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
    string label;
    
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
    void setX(float x);
    float getY();
    float getRadius();
    string getLabel();
    
    bool checkOnScreen();
    
    void changeDirection(int nextDirection);
    void select();
    void deselect();
    
    /* Switches value of isToggled
    */
    void toggleisTopped();
    
    /* Moves ball out and makes stack and queue related bools: isPushed and isTopped to default false values when ball is popped out of the stack or queue.
    */
    void ballOut();
    
    /* Checks if next available path junction allows the ball to move in the direction that the player wishes.
     */
    bool onPath(float x, float y);
    
    /* When the ball is about to derail off the path, this function is automatically called and returns the next the appropriate direction to move.
     */
    int searchPath(float x, float y);
    //TODO: make more efficient?
    void move();
    //TODO: make more efficient?
    void update(bool status);
    void draw();
};

#endif /* Ball_hpp */
