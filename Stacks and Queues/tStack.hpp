//Stacks and Queues
//Copyright © 2016 TeamSQ. All rights reserved.

//tStack.hpp

#ifndef tStack_hpp
#define tStack_hpp

#include <stack> //for std::stack

#include "Ball.hpp"

class tStack {
private:
    std::stack<Ball> toolStack;
    float x, y;
    float width, height;
    
public:
    tStack(float x, float y, float width, float height);
    int size();
    
    void push(Ball ball);
    void pop();
    Ball top();
    void update();
    void draw();
};

#endif /* tStack_hpp */
