//Stacks and Queues
//Copyright © 2016 TeamSQ. All rights reserved.

//tStack.cpp

#include "tStack.hpp"

tStack::tStack(float x, float y, float width, float height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

float tStack::getX() {
    return x;
}

float tStack::getY() {
    return y;
}

float tStack::getWidth() {
    return width;
}

float tStack::getHeight() {
    return height;
}

int tStack::size() {
    return toolStack.size();
}

void tStack::push(Ball ball) {
    toolStack.push(ball);
}

//TODO: test
void tStack::pop() {
    if(size()==0) return;
    toolStack.top().isPushed = false;
    toolStack.pop();
}
//TODO: test

Ball tStack::top() {
    return toolStack.top();
}

//TODO: test
void tStack::checkForSelect(float x, float y, string action) {
    cout << "from stack.cpp: x = " << this->x << ", " << x << " y = " << this->y << ", " << y << " action = " << action << ".\n";
    if(x <= this->x+(width/2.0) && x >= this->x-(width/2.0) && y <= this->y+(height/2.0) && y >= this->y-(height/2.0)) {
        if(action.compare("pop") == 0) pop();
        else if(action.compare("top") == 0) top();
    }
}
//TODO: test

void tStack::update() {
    //TODO: it is currently stationary but planning to have an animation when it pops.
}

//need to make it better than a yellow rectangle
void tStack::draw() {
    sf::RectangleShape stack;
    stack.setFillColor(sf::Color::Color(255, 165, 0));
    stack.setSize(sf::Vector2f(width, height));
    stack.setPosition(x, y);
    stack.setOrigin(width/2.0, height/2.0);
    window->draw(stack);
}
