//Stacks and Queues
//Copyright © 2016 TeamSQ. All rights reserved.

//Level.cpp

#include "Level.hpp"

Level::Level(int num) {
    ballsPositionX = { RES_X, RES_X , RES_X };
    ballsPositionY = { RES_Y2, RES_Y2, RES_Y };
    ballsPeriod = { 1.0, 2.0, 2.0 };
    ballsVX = { 1.0, 1.0, 1.0 };
    ballsRadii = { 10, 10, 10 };
    
    this->num = num;
    isActive = true;
}
    
float Level::getBallPositionX() {
    return ballsPositionX.at(num);
}
    
float Level::getBallPositionY() {
    return ballsPositionY.at(num);
}
    
float Level::getBallVX() {
    return ballsVX.at(num);
}
    
float Level::getBallPeriod() {
    return ballsPeriod.at(num);
}
    
float Level::getBallRadius() {
    return ballsRadii.at(num);
}
    
void Level::startBallClock() {
    ballClock = clock();
}
    
float Level::getInterval() {
    clock_t interval;
    interval = clock() - ballClock;
    return (((float)interval)/(CLOCKS_PER_SEC))*6;
}
    
void Level::updateLevel() {
        
    for( int i = 0; i < balls.size(); i = i + 1 ) {
        //cout << "Ball " << i << ":";
            
        //ball went through exit tube
        if(!balls.at(i).isActive) {
            continue;
        }
            
        //before ball starts moving
        if(!(balls.at(i).isMoving)) {
            if(i == 0) {
                //cout << "Ball 0 updated and moving" << ".\n";
                balls.at(i).update(true);
                startBallClock();
            }
            else {
                //cout << getInterval();
                if(getInterval() >= ballsPeriod.at(num)) {
                    //cout << " Ball " << i << " moved after right interval" << ".\n";
                    balls.at(i).update(true);
                    startBallClock();
                }
            }
        }
        //after ball is moving
        else {
            //cout << "Ball " << i << "is already moving" << ".\n";
            balls.at(i).update(true);
        }
    }
}

//need to make it better than a white rectangle
void Level::drawInTube() {
    float width = (ballsRadii.at(num)*2)*3; //can hold three balls at a time
    float height = ballsRadii.at(num)*2;
    sf::RectangleShape inTube;
    inTube.setFillColor(sf::Color::White);
    inTube.setSize(sf::Vector2f(width, height));
    inTube.setPosition(RES_X-width/2.0, RES_Y2);
    inTube.setOrigin(width/2.0, height/2.0);
    window->draw(inTube);
}

void Level::drawOutTube() {
    //TODO: Draw similiar tube on opposite end of screen
}
    
void Level::drawLevel() {
    drawInTube();
    drawOutTube();
    for( int i = 0; i < balls.size(); i = i + 1 ) {
        balls.at(i).draw();
    }
}

void clearLevel() {
        //TODO: clear all level items when off screen
}
