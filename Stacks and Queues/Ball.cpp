//Stacks and Queues
//Copyright © 2016 TeamSQ. All rights reserved.

//Ball.cpp

#include "Ball.hpp"

Ball::Ball(int num, float x, float y, float vx, float vy, float radius, sf::Color color, sf::String label) {
    
    this->num = num;
    this->x = x;
    this->y = y;
    this->vx = vx;
    this->vy = vy;
    this->radius = radius;
    dia = radius*2;
    this->color = color;
    this->label = label;
    
    isActive = true;
    isMoving = false;
    
    if(num == 1)isSelected = true;
    else isSelected = false;
    currDirection = 1;
    nextDirection = 1;
}

bool Ball::checkOnScreen() {
    if (x < -(radius) || y < -(radius) || x > RES_X + x || y > RES_Y + y) {
        return false;
    }
    return true;
}

void Ball::move() {
    //1 = left, 2 = up, 3 = down, can't go right
    if(currDirection != nextDirection) {
        //tryTurning(nextDirection);
    }
    
    switch(currDirection) {
        case 1: x -= vx; break;
        case 2: y -= vy; break;
        case 3: y += vy; break;
    }
    
}
