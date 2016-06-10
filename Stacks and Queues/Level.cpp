//Stacks and Queues
//Copyright © 2016 TeamSQ. All rights reserved.

//Level.cpp

#include "Level.hpp"

Level::Level(int num) {
    inTubePositionX = { RES_X, RES_X , RES_X };
    inTubePositionY = { RES_Y2, RES_Y2, RES_Y };
    inTubePosX = inTubePositionX.at(num);
    inTubePosY = inTubePositionY.at(num);
    
    ballsPeriod = { 1.0, 2.0, 2.0 };
    ballsVX = { 1.0, 1.0, 1.0 };
    ballsRadii = { 10, 10, 10 };
    
    this->num = num;
    isActive = true;
    selectedBall = 0;
}

float Level::getInTubePositionX() {
    return inTubePositionX.at(num);
}

float Level::getInTubePositionY() {
    return inTubePositionY.at(num);
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

float Level::abs(float num) {
    if(num < 0) return (-num);
    return num;
}

void Level::startBallClock() {
    ballClock = clock();
}

float Level::getInterval() {
    clock_t interval;
    interval = clock() - ballClock;
    return (((float)interval)/(CLOCKS_PER_SEC))*6;
}

int Level::prevBall() {
    balls.at(selectedBall).deselect();
    if(selectedBall == 0) {
        selectedBall = balls.size()-1;
    }
    else selectedBall--;
    balls.at(selectedBall).select();
    return selectedBall;
}

int Level::nextBall() {
    balls.at(selectedBall).deselect();
    if(selectedBall == balls.size()-1) {
        selectedBall = 0;
    }
    else selectedBall++;
    balls.at(selectedBall).select();
    return selectedBall;
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
    inTube.setPosition(inTubePosX-width/2.0, inTubePosY);
    window->draw(inTube);
    
    sf::CircleShape leftEnd;
    leftEnd.setFillColor(inner);
    leftEnd.setOutlineColor(sf::Color::Black);
    leftEnd.setOutlineThickness((height/5.0)); //Thickness can be negative so that the outline expands from the border towards center instead of increasing the shape's size.
    leftEnd.setRadius(height/2);
    leftEnd.setOrigin(width/2.0, height/2.0);
    leftEnd.setPosition(inTubePosX-width*(2.0/3.0), inTubePosY);
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
    outTube.setOutlineThickness(height/5.0);
    outTube.setSize(sf::Vector2f(width, height));
    outTube.setOrigin(width/2.0, height/2.0);
    outTube.setPosition(RES_X-(inTubePosX-width/2.0), inTubePosY);
    window->draw(outTube);
    
    sf::CircleShape rightEnd;
    rightEnd.setFillColor(inner);
    rightEnd.setOutlineColor(sf::Color::Black);
    rightEnd.setOutlineThickness((height/5.0)); //Thickness can be negative so that the outline expands from the border towards center instead of increasing the shape's size.
    rightEnd.setRadius(height/2);
    rightEnd.setOrigin(width/2.0, height/2.0);
    rightEnd.setPosition(RES_X-(inTubePosX-width*(4.0/3.0)), inTubePosY);
    window->draw(rightEnd);
}

void Level::drawPath() {
    float pathWidth = (ballsRadii.at(num)*25.0);
    float pathHeight = (ballsRadii.at(num)*2.0)/5.0; //inTube height/5.0
    
    //have to switch width and height to make vertical
    float inVerticalWidth = pathHeight;
    float inVerticalHeight = 0.0;
    float inVerticalY = inTubePosY;
    
    float directLineWidth = inTubePosX - (RES_X - inTubePosX) - (pathWidth*2.0);
    float directLineHeight = pathHeight;
    
    float leftLine1Width = 0.0;
    float leftLine1Height = pathHeight;
    
    float leftLine2Width = 0.0;
    float leftLine2Height = pathHeight;
    
    float outVerticalWidth = pathHeight;
    float outVerticalHeight = 0.0;
    
    sf::RectangleShape directLine;
    directLine.setFillColor(lineColor);
    directLine.setOutlineColor(lineOutlineColor);
    directLine.setOutlineThickness(pathHeight/5.0);
    directLine.setSize(sf::Vector2f(directLineWidth, directLineHeight));
    directLine.setOrigin(directLineWidth/2.0, directLineHeight/2.0);
    directLine.setPosition(RES_X/2.0, inTubePosY);
    window->draw(directLine);
    
    //path coming out of inTube
    sf::RectangleShape inLine;
    inLine.setFillColor(lineColor);
    inLine.setOutlineColor(lineOutlineColor);
    inLine.setOutlineThickness(pathHeight/5.0);
    inLine.setSize(sf::Vector2f(pathWidth, pathHeight));
    inLine.setOrigin(pathWidth/2.0, pathHeight/2.0);
    inLine.setPosition(inTubePosX-pathWidth/2.0, inTubePosY);
    window->draw(inLine);
    
    //path coming out of outTube
    sf::RectangleShape outLine;
    outLine.setFillColor(lineColor);
    outLine.setOutlineColor(lineOutlineColor);
    outLine.setOutlineThickness(pathHeight/5.0);
    outLine.setSize(sf::Vector2f(pathWidth, pathHeight));
    outLine.setOrigin(pathWidth/2.0, pathHeight/2.0);
    outLine.setPosition(RES_X-(inTubePositionX.at(num)-pathWidth/2.0), RES_Y-inTubePosY);
    window->draw(outLine);
    
    for(int i=0; i<stacks.size(); i++) {
        tStack currStack = stacks.at(i);
        
        //cout << "There is something in the stack vector.\n";
        inVerticalHeight = abs(inTubePosY - abs(currStack.y-currStack.height/2.0));
        outVerticalHeight = abs((RES_Y-inTubePosY) - abs(currStack.y-currStack.height/2.0));
        
        if(currStack.y >= inTubePosY) inVerticalY = abs(inTubePosY+(inVerticalHeight/2.0));
        else inVerticalY = abs(inTubePosY-(inVerticalHeight/2.0));
        
        leftLine1Width = abs(currStack.x - (inTubePosX-pathWidth));
        leftLine2Width = ((RES_X - (inTubePosX-pathWidth)) - currStack.x);
        
        sf::RectangleShape inVertical;
        inVertical.setFillColor(lineColor);
        inVertical.setOutlineColor(lineOutlineColor);
        inVertical.setOutlineThickness(pathHeight/5.0);
        inVertical.setSize(sf::Vector2f(inVerticalWidth, inVerticalHeight));
        inVertical.setOrigin(inVerticalWidth/2.0, inVerticalHeight/2.0);
        inVertical.setPosition(inTubePosX-pathWidth, inVerticalY);
        window->draw(inVertical);
        
        sf::RectangleShape leftLine1;
        leftLine1.setFillColor(lineColor);
        leftLine1.setOutlineColor(lineOutlineColor);
        leftLine1.setOutlineThickness(pathHeight/5.0);
        leftLine1.setSize(sf::Vector2f(leftLine1Width, leftLine1Height));
        leftLine1.setOrigin(leftLine1Width/2.0, leftLine1Height/2.0);
        leftLine1.setPosition(abs(abs(inTubePositionX.at(num)-pathWidth) - leftLine1Width/2.0), abs(currStack.height/2.0 - currStack.y));
        window->draw(leftLine1);
        
        sf::RectangleShape outVertical;
        outVertical.setFillColor(lineColor);
        outVertical.setOutlineColor(lineOutlineColor);
        outVertical.setOutlineThickness(pathHeight/5.0);
        outVertical.setSize(sf::Vector2f(outVerticalWidth, outVerticalHeight));
        outVertical.setOrigin(outVerticalWidth/2.0, outVerticalHeight/2.0);
        outVertical.setPosition(RES_X-(inTubePositionX.at(num)-pathWidth), inVerticalY);
        window->draw(outVertical);
        
        sf::RectangleShape leftLine2;
        leftLine2.setFillColor(lineColor);
        leftLine2.setOutlineColor(lineOutlineColor);
        leftLine2.setOutlineThickness(pathHeight/5.0);
        leftLine2.setSize(sf::Vector2f(leftLine2Width, leftLine2Height));
        leftLine2.setOrigin(leftLine2Width/2.0, leftLine2Height/2.0);
        leftLine2.setPosition(abs(abs(RES_X - (inTubePosX-pathWidth)) - leftLine2Width/2.0), abs(currStack.height/2.0 - currStack.y));
        window->draw(leftLine2);
    }
    //cout << "Stack paths drawn.\n";
}

void Level::drawLevel() {
    drawInTube();
    drawOutTube();
    drawPath();
    
    //balls drawn after tubes makes tubes transparent
    for( int i = 0; i < balls.size(); i++ ) {
        balls.at(i).draw();
    }
    //stacks drawn after balls make stacks obscure
    for(int i=0; i<stacks.size(); i++) {
        stacks.at(i).draw();
    }
}

void Level::clearLevel() {
    balls.clear();
    stacks.clear();
}
