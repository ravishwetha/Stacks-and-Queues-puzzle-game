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
    
    if(num == 0) isSelected = true;
    else isSelected = false;
    selectColor = sf::Color::Green;
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

void Ball::select() {
    isSelected = true;
}

void Ball::deselect() {
    isSelected = false;
}

void Ball::update(bool status) {
    isOnScreen = checkOnScreen();
    
    isMoving = status;
    if(!isMoving || !isActive) return;
    move();
    if (x < -(dia) || y < -(dia)) isActive = false;
}

void Ball::draw() {
    if(!isOnScreen || !isActive) return;
    
    sf::Color drawColor;
    
    if(isSelected) drawColor = selectColor;
    else drawColor = color;
    
    sf::CircleShape ballCircle;
    ballCircle.setFillColor(drawColor);
    ballCircle.setRadius(radius);
    ballCircle.setPosition(x, y);
    ballCircle.setOrigin(radius, radius);
    
    //place label on ball
    // Declare and load a font
    sf::Font ballFont;
    ballFont.loadFromFile("sansation.ttf"); //insert correct file path
    // Create a text
    sf::Text ballText(label, ballFont);
    ballText.setCharacterSize(dia);
    ballText.setStyle(sf::Text::Bold);
    ballText.setColor(sf::Color::White);
    //ballText.setOrigin(x+radius, y+radius);
    ballText.setPosition(x-(radius/1.50), y-(radius/0.75));
    
    window->draw(ballCircle);
    window->draw(ballText);
}
