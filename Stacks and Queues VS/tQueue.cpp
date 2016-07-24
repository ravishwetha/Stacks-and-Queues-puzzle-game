//Stacks and Queues
//Copyright © 2016 TeamSQ. All rights reserved.

//tQueue.cpp

#include "tQueue.hpp"

tQueue::tQueue(float x, float y, float width, float height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    
    this->topLeftX = x-width/2.0;
    this->topLeftY = y-height/2.0;
    this->bottomRightX = x+width/2.0;
    this->bottomRightY = y-height/2.0;
}

float tQueue::getX() {
    return x;
}

float tQueue::getY() {
    return y;
}

float tQueue::getWidth() {
    return width;
}

float tQueue::getHeight() {
    return height;
}

float tQueue::gettopLeftX() {
    return topLeftX;
}

float tQueue::gettopLeftY() {
    return topLeftY;
}

float tQueue::getbottomRightX() {
    return bottomRightX;
}

float tQueue::getbottomRightY() {
    return bottomRightY;
}

int tQueue::size() {
    return toolQueue.size();
}

void tQueue::push(Ball ball) {
    toolQueue.push(ball);
}

void tQueue::pop() {
    if(size() == 0) {
        return;
    }
    cout << "front Ball: " << toolQueue.front().num << " is not pushed anymore.\n";
    toolQueue.pop();
}

Ball tQueue::front() {
    if(size() == 0) {
        return;
    }
    //cout << "draw top Ball: " << toolQueue.front().num << ".\n";
    toolQueue.front().draw();
    return toolQueue.front();
}

bool tQueue::checkForSelect(float x, float y) {
    if(x <= this->x+(width/2.0) && x >= this->x-(width/2.0) && y <= this->y+(height/2.0) && y >= this->y-(height/2.0)) {
        return true;
    }
    return false;
}

void tQueue::update() {
    //TODO: it is currently stationary but planning to have an animation when it pops.
}

//TODO: need to make it better than a orange rectangle
void tQueue::draw() {
    sf::RectangleShape stack;
    stack.setFillColor(sf::Color::Color(255, 165, 0));
    stack.setSize(sf::Vector2f(width, height));
    stack.setPosition(x, y);
    stack.setOrigin(width/2.0, height/2.0);
    window->draw(stack);
}