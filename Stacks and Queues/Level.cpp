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
    
    //UPDATE BALLS//
    for( int i=0; i<balls.size(); i = i + 1 ) {
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
        
        //UPDATE STACKS//
        for(int i=0; i<stacks.size(); i++) {
            stacks.at(i).update();
        }
    }
}

//need to make it better than a white rectangle
void Level::drawInTube() {
    float width = (ballsRadii.at(num)*2)*3; //can hold three balls at a time
    float height = ballsRadii.at(num)*2;
    
    sf::Color inner = sf::Color::Color(128, 128, 128); //currently gray 128
    sf::Color outer = sf::Color::Color(192, 192, 192); //currently silver 192
    
    //inTube base rectangle
    sf::RectangleShape inTube;
    inTube.setFillColor(outer);
    inTube.setOutlineColor(sf::Color::Black);
    inTube.setOutlineThickness((height/5.0));
    inTube.setSize(sf::Vector2f(width, height));
    inTube.setOrigin(width/2.0, height/2.0);
    inTube.setPosition(RES_X-width/2.0, RES_Y2);
    window->draw(inTube);
    
    sf::CircleShape leftEnd;
    leftEnd.setFillColor(inner);
    leftEnd.setOutlineColor(sf::Color::Black);
    leftEnd.setOutlineThickness(height/5.0); //Thickness can be negative so that the outline expands from the border towards center instead of increasing the shape's size.
    leftEnd.setRadius(height/2);
    leftEnd.setOrigin(width/2.0, height/2.0);
    leftEnd.setPosition(RES_X - width*(2.0/3.0), RES_Y2);
    window->draw(leftEnd);
}

void Level::drawOutTube() {
    float width = (ballsRadii.at(num)*2)*3; //can hold three balls at a time
    float height = ballsRadii.at(num)*2;
    
    sf::Color inner = sf::Color::Color(128, 128, 128); //currently gray 128
    sf::Color outer = sf::Color::Color(192, 192, 192); //currently silver 192
    
    //inTube base rectangle
    sf::RectangleShape outTube;
    outTube.setFillColor(outer);
    outTube.setOutlineColor(sf::Color::Black);
    outTube.setOutlineThickness((height/5.0));
    outTube.setSize(sf::Vector2f(width, height));
    outTube.setOrigin(width/2.0, height/2.0);
    outTube.setPosition(width/2.0, RES_Y2);
    window->draw(outTube);
    
    sf::CircleShape rightEnd;
    rightEnd.setFillColor(inner);
    rightEnd.setOutlineColor(sf::Color::Black);
    rightEnd.setOutlineThickness((height/5.0)); //Thickness can be negative so that the outline expands from the border towards center instead of increasing the shape's size.
    rightEnd.setRadius(height/2);
    rightEnd.setOrigin(width/2.0, height/2.0);
    rightEnd.setPosition(width*(4.0/3.0), RES_Y2);
    window->draw(rightEnd);
}
    
void Level::drawLevel() {
    drawInTube();
    drawOutTube();
    
    //balls drawn after tubes makes tubes transparent
    for( int i = 0; i < balls.size(); i++ ) {
        balls.at(i).draw();
    }
    //stacks drawn after balls make stacks obscure
    for(int i=0; i<stacks.size(); i++) {
        stacks.at(i).draw();
    }
}

void clearLevel() {
        //TODO: clear all level items when level ends
}
