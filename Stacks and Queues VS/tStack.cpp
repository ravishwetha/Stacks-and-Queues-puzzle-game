//Stacks and Queues
//Copyright © 2016 TeamSQ. All rights reserved.

//tStack.cpp

#include "stdafx.h"
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

void tStack::pop() {
    if(size() == 0) {
        return;
    }
    cout << "top Ball: " << toolStack.top().num << " is not pushed anymore.\n";
    toolStack.pop();
}

Ball tStack::top() {
    if(size() == 0) {
        return;
    }
    cout << "draw top Ball: " << toolStack.top().num << ".\n";
    toolStack.top().draw();
    return toolStack.top();
}

bool tStack::checkForSelect(float x, float y) {
    if(x <= this->x+(width/2.0) && x >= this->x-(width/2.0) && y <= this->y+(height/2.0) && y >= this->y-(height/2.0)) {
        return true;
    }
    return false;
}

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
