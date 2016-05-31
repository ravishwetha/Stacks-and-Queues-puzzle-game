//Stacks and Queues
//Copyright © 2016 TeamSQ. All rights reserved.

//Ball.cpp

#include "Ball.hpp"

Ball::Ball(float x, float y, float vx, float vy, float radius, sf::Color color, sf::String label) {
    
        this->x = x;
        this->y = y;
        this->vx = vx;
        this->vy = vy;
        this->radius = radius;
        this->color = color;
        this->label = label;
        
        dia = radius*2;
        isActive = true;
        isMoving = false;
}
    
bool Ball::checkOnScreen() {
    if (x < -(radius) || y < -(radius) || x > RES_X + x || y > RES_Y + y) {
        return false;
    }
    return true;
}
    
void Ball::update(bool status) {
    isOnScreen = checkOnScreen();
        
    isMoving = status;
    if(!isMoving || !isActive) return;
    x -= vx;
    
    if (x < -(dia) || y < -(dia)) isActive = false;
}
    
void Ball::draw() {
    if(!isOnScreen || !isActive) return;
        
    sf::CircleShape ballCircle;
    ballCircle.setFillColor(color);
    ballCircle.setRadius(radius);
    ballCircle.setPosition(x, y);
    ballCircle.setOrigin(radius, radius);
        
    //place label on ball
    // Declare and load a font
    sf::Font ballFont;
    ballFont.loadFromFile("/Users/ravi/Documents/Orbital/Stacks and Queues/Stacks and Queues/sansation.ttf");
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
