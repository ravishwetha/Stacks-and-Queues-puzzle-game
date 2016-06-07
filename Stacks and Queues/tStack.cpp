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

int tStack::size() {
    return toolStack.size();
}

void tStack::push(Ball ball) {
    toolStack.push(ball);
}

void tStack::pop() {
    toolStack.pop();
}

Ball tStack::top() {
    return toolStack.top();
}

void tStack::update() {
    //TODO: it is currently stationary but planning to have an animation when it pops. Also, player can view a menu of the possible functions to use with the stack when they click on it.
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
