//Stacks and Queues
//Copyright © 2016 TeamSQ. All rights reserved.

//Level.cpp

#include "Level.hpp"

Level::Level(int num, std::vector<string> winOrder) {
    inTubePosX = inTubePositionX.at(num);
    inTubePosY = inTubePositionY.at(num);
    
    this->num = num;
    if(num == 0) unlocked = true;
    else unlocked = false;
    this->winOrder = winOrder;
    levelBarLabel = makeLevelBarLabel();
    
    isActive = true;
    ballsInitiated = false;
    selectedBall = 0;
    
    pathStored = false;
    float inVerticalXdot = 0;
    float inVerticalYdot = 0;
}

float Level::getInTubePositionX() {
    return inTubePosX;
}

float Level::getInTubePositionY() {
    return inTubePosY;
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

bool Level::toggleUnlocked() {
    if(unlocked) unlocked = false;
    else unlocked = true;
    return unlocked;
}

float Level::abs(float num) {
    if(num < 0) return (-num);
    return num;
}

float Level::min(float a, float b) {
    if(a == b) return 0;
    else if(a < b) return a;
    return b;
}

int Level::min(int a, int b) {
    if(a == b) return 0;
    else if(a < b) return a;
    return b;
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
    //cout << "current: " << selectedBall << " next: ";
    balls.at(selectedBall).deselect();
    if(selectedBall == 0) {
        selectedBall = balls.size()-1;
    }
    else selectedBall--;
    //cout << selectedBall << ".\n";
    balls.at(selectedBall).select();
    return selectedBall;
}

int Level::nextBall() {
    //cout << "current: " << selectedBall << " next: ";
    balls.at(selectedBall).deselect();
    if(selectedBall == balls.size()-1) {
        selectedBall = 0;
    }
    else selectedBall++;
    //cout << selectedBall << ".\n";
    balls.at(selectedBall).select();
    return selectedBall;
}

int Level::checkForSPush() {
    
    for(int i=0; i<balls.size(); i++) {
        Ball currBall = balls.at(i);
        if(currBall.isPushed) continue;
        
        for(int j=0; j<stacks.size(); j++) {
            tStack currStack = stacks.at(j);
            
            //if(currBall.getX() == currStack.getX()) cout << currBall.getY() << ", " << (currStack.getY() - currStack.getHeight()/2.0) << ".\n";
            if(currBall.getX() == currStack.getX() && currBall.getY() >= (currStack.getY()-(currStack.getHeight()/2.0) - currBall.getRadius()) && currBall.getY() <= (currStack.getY()-(currStack.getHeight()/2.0))) {
                
                //cout << "ball pushed\n";
                balls.at(i).isPushed = true;
                stacks.at(j).push(currBall);
                return j;
            }
        }
    }
}

int Level::checkForQPush() {
    
    for(int i=0; i<balls.size(); i++) {
        Ball currBall = balls.at(i);
        if(currBall.isPushed) continue;
        
        for(int j=0; j<queues.size(); j++) {
            tQueue currQueue = queues.at(j);
            
            //cout << currBall.getY() << ", " << currQueue.getY() << ", " << currBall.getX() << ", " << (currQueue.getX() + currQueue.getWidth()/2.0) << ".\n";
            if(currBall.getX() <= (currQueue.getX()+(currQueue.getWidth()/2.0) + currBall.getRadius()) && currBall.getX() >= (currQueue.getX()+(currQueue.getWidth()/2.0)) && (currBall.getY() + 1 == currQueue.getY() || currBall.getY() - 2 == currQueue.getY())) {
            
            //if(currBall.getX() >= currQueue.gettopLeftX() && currBall.getY() >= currQueue.gettopLeftY() && currBall.getX() <= currQueue.getbottomRightX() && currBall.getY() <=currQueue.getbottomRightY()); { //alternative solution: checks if center of ball is in queue
                
                //cout << "ball pushed\n";
                balls.at(i).isPushed = true;
                float currBallNewX = currBall.getX() - currQueue.getWidth();
                balls.at(i).setX(currBallNewX);
                queues.at(j).push(currBall);
                return j;
            }
        }
    }
}

void Level::checkForSQSelect(float x, float y, string action) {
    int topBallID;

    for(int i=0; i<stacks.size(); i++) {
        if(stacks.at(i).checkForSelect(x, y) && stacks.at(i).size() != 0) {
            //cout << "from level.cpp: stack " << i << ".\n";
            topBallID = stacks.at(i).top().num;
            if(action.compare("pop") == 0) {
                //cout << "from level.cpp: pop " << topBallID << ".\n";
                balls.at(topBallID).ballOut();
                stacks.at(i).pop();
            }
            else if(action.compare("peek") == 0) {
                //cout << "from level.cpp: top.\n";
                balls.at(topBallID).toggleisTopped();
                stacks.at(i).top();
            }
        }
    }
    
    int frontBallID;
    
    for(int i=0; i<queues.size(); i++) {
        if(queues.at(i).checkForSelect(x, y) && queues.at(i).size() != 0) {
            //cout << "from level.cpp: queue " << i << ".\n";
            frontBallID = queues.at(i).front().num;
            if(action.compare("pop") == 0) {
                //cout << "from level.cpp: pop " << frontBallID << ".\n";
                balls.at(frontBallID).ballOut();
                queues.at(i).pop();
            }
            else if(action.compare("peek") == 0) {
                //cout << "from level.cpp: front.\n";
                balls.at(frontBallID).toggleisTopped();
                queues.at(i).front();
            }
        }
    }
}

int Level::checkForWin() {
    if(winOrder.empty() || balls.empty()) {
        if(winOrder.empty() && balls.empty()) cout << "Everythang empty.\n";
        else if(winOrder.empty()) cout << "winOrder empty.\n";
        else if(balls.empty()) cout << "balls empty.\n";
        return 1;
    }
    
    for(int i=0; i<balls.size(); i++) {
        if(!balls.at(i).isActive) {
            if(winOrder.size() == 1 && balls.at(i).getLabel() == winOrder.front()) {
                return 1;
            }
            else if(balls.at(i).getLabel() == winOrder.front()) {
                balls.erase(balls.begin() + i);
                winOrder.erase(winOrder.begin());
                continue;
            }
            else {
                return -1;
            }
        }
    }
    return 0;
}

int Level::updateLevel() {
    if(!isActive) return;
    
    int recentStack = checkForSPush();
    int recentQueue = checkForQPush();
    
    //cout << "From updateLevel(), Level " << num+1 << " has " << balls.size() << " balls.\n";
    //UPDATE BALLS//
    for(int i=0; i<balls.size(); i++) {
        //ball went through exit tube
        if(!balls.at(i).isActive) {
            //cout << "Ball " << balls.at(i).getLabel() << " i = " << i << " at(" << balls.at(i).getX() << ", " << balls.at(i).getY() << ") is not active\n";
            continue;
        }
        //else cout << "Ball " << balls.at(i).getLabel() << " i = " << i << " at(" << balls.at(i).getX() << ", " << balls.at(i).getY() << ") is active\n";
        
        //before ball enter level
        if(!(balls.at(i).isMoving) && !ballsInitiated) {
            if(i == 0) {
                balls.at(i).update(true);
                startBallClock();
            }
            else {
                if(getInterval() >= ballsPeriod.at(num)) {
                    balls.at(i).update(true);
                    if(i == balls.size()-1) ballsInitiated = true; // last ball entered level
                    else startBallClock();
                }
            }
        }
        //after ball entered level
        else {
            balls.at(i).update(true);
        }
    }
    
    //UPDATE STACKS AND QUEUES//
    for(int i=0; i<queues.size(); i++) {
        queues.at(i).update();
    }
    for(int i=0; i<stacks.size(); i++) {
        stacks.at(i).update();
    }
        
    status = checkForWin();
    switch(status) {
        case 0: break; //level is ongoing
        case -1: isActive = false; levelBarLabel = "LOSS"; break;
        case 1: isActive = false; levelBarLabel = "WIN"; break;
        default: isActive = false; levelBarLabel = "ERROR"; break;
    }
    return status;
}

string Level::makeLevelBarLabel() {
    string label;
    for(int i=0; i<winOrder.size(); i++) {
        label.append(winOrder.at(i));
        if(i != winOrder.size()-1) label.append(" ,");
    }
    return label;
}

void Level::drawLevelBar() {
    float width = RES_X/4.0; //can hold three balls at a time
    float height = RES_Y/10.0;
    float x = RES_X/2.0;
    float y = RES_Y - (height/2.0);
    
    sf::Color color = sf::Color::Color(186, 85, 211); //currently gray 128
    
    sf::RectangleShape levelBar;
    levelBar.setFillColor(color);
    levelBar.setOutlineColor(sf::Color::Black);
    levelBar.setOutlineThickness((height/50.0));
    levelBar.setSize(sf::Vector2f(width, height));
    levelBar.setOrigin(width/2.0, height/2.0);
    levelBar.setPosition(x, y);
    window->draw(levelBar);
    
    if(levelBarLabel.empty()) return;
    float size = min(width/2.0, height)/2.0;
    
    // Declare and load a font
    sf::Font barFont;
    barFont.loadFromFile(rPath + "sansation.ttf");
    // Create a text
    sf::Text barText(levelBarLabel, barFont);
    barText.setCharacterSize(size);
    barText.setStyle(sf::Text::Bold);
    barText.setColor(sf::Color::White);
    barText.setOrigin(levelBar.getOrigin());
    barText.setPosition(x + width/((size/10.0)*0.75), y);
    window->draw(barText);
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

void Level::drawStandardPath() {
    float pathWidth = (ballsRadii.at(num)*25.0);
    float pathHeight = (ballsRadii.at(num)*2.0)/5.0; //inTube height/5.0
    
    float directLineWidth = inTubePosX - (RES_X - inTubePosX) - (pathWidth*2.0);
    float directLineHeight = pathHeight;
    
    //movement index:
    
    sf::RectangleShape directLine;
    directLine.setFillColor(lineColor);
    directLine.setOutlineColor(lineOutlineColor);
    directLine.setOutlineThickness(pathHeight/5.0);
    directLine.setSize(sf::Vector2f(directLineWidth, directLineHeight));
    directLine.setOrigin(directLineWidth/2.0, directLineHeight/2.0);
    directLine.setPosition(RES_X/2.0, inTubePosY);
    window->draw(directLine);
    
    if(pathCoords.empty()) {
    pathCoords.push_back(RES_X/2.0 - directLineWidth/2.0);
    pathCoords.push_back(inTubePosY - directLineHeight/2.0);
    pathCoords.push_back(RES_X/2.0 + directLineWidth/2.0);
    pathCoords.push_back(inTubePosY + directLineHeight/2.0);
    pathCoords.push_back(leftF);
    }
    
    //path coming out of inTube
    sf::RectangleShape inLine;
    inLine.setFillColor(lineColor);
    inLine.setOutlineColor(lineOutlineColor);
    inLine.setOutlineThickness(pathHeight/5.0);
    inLine.setSize(sf::Vector2f(pathWidth, pathHeight));
    inLine.setOrigin(pathWidth/2.0, pathHeight/2.0);
    inLine.setPosition(inTubePosX-pathWidth/2.0, inTubePosY);
    window->draw(inLine);
    
    if(!pathStored) {
    pathCoords.push_back(inTubePosX - pathWidth);
    pathCoords.push_back(inTubePosY - pathHeight/2.0);
    pathCoords.push_back(inTubePosX);
    pathCoords.push_back(inTubePosY + pathHeight/2.0);
    pathCoords.push_back(leftF);
    }
    
    //path coming out of outTube
    sf::RectangleShape outLine;
    outLine.setFillColor(lineColor);
    outLine.setOutlineColor(lineOutlineColor);
    outLine.setOutlineThickness(pathHeight/5.0);
    outLine.setSize(sf::Vector2f(pathWidth, pathHeight));
    outLine.setOrigin(pathWidth/2.0, pathHeight/2.0);
    outLine.setPosition(RES_X-(inTubePosX-pathWidth/2.0), RES_Y-inTubePosY);
    window->draw(outLine);
    
    if(!pathStored) {
    pathCoords.push_back(RES_X-inTubePosX);
    pathCoords.push_back(RES_Y-inTubePosY - pathHeight/2.0);
    pathCoords.push_back((RES_X-inTubePosX) + pathWidth);
    pathCoords.push_back(RES_Y-inTubePosY + pathHeight/2.0);
    pathCoords.push_back(leftF);
    }
}

void Level::drawQueuePath() {
    float pathWidth = (ballsRadii.at(num)*25.0); //strictly horizontal measure
    float pathHeight = (ballsRadii.at(num)*2.0)/5.0; //inTube height/5.0, strictly vertical measure
    
    //have to switch width and height to make vertical
    float VerticalAdjustmentY = -1.0;
    float leftLinePosY = 0;
    
    float inVerticalWidth = pathHeight;
    float inVerticalHeight = 0.0;
    float inVerticalY = inTubePosY;
    
    float leftLine1Width = 0.0;
    float leftLine1Height = pathHeight;
    
    float leftLine2Width = 0.0;
    float leftLine2Height = pathHeight;
    
    float outVerticalWidth = pathHeight;
    float outVerticalHeight = 0.0;
    
    for(int i=0; i<queues.size(); i++) {
        tQueue currQueue = queues.at(i);
        
        inVerticalHeight = abs(inTubePosY - currQueue.getY());
        outVerticalHeight = abs((RES_Y-inTubePosY) - currQueue.getY());
        
        if(currQueue.getY() > inTubePosY) inVerticalY = (inTubePosY+(inVerticalHeight/2.0));
        else inVerticalY = abs(inTubePosY-(inVerticalHeight/2.0));
        
        leftLinePosY = currQueue.getY();
        leftLine1Width = abs(currQueue.getX() - (inTubePosX-pathWidth));
        leftLine2Width = ((RES_X - (inTubePosX-pathWidth)) - currQueue.getX());
        
        sf::RectangleShape inVertical;
        inVertical.setFillColor(lineColor);
        inVertical.setOutlineColor(lineOutlineColor);
        inVertical.setOutlineThickness(pathHeight/5.0);
        inVertical.setSize(sf::Vector2f(inVerticalWidth, inVerticalHeight));
        inVertical.setOrigin(inVerticalWidth/2.0, inVerticalHeight/2.0);
        inVertical.setPosition(inTubePosX-pathWidth, inVerticalY);
        window->draw(inVertical);
        
        if(!pathStored) {
            pathCoords.push_back(inTubePosX-pathWidth - inVerticalWidth/2.0);
            if(currQueue.getY() > inTubePosY) { //queue is below center
                pathCoords.push_back(abs(inVerticalY - inVerticalHeight/2.0) + pathHeight);
                pathCoords.push_back(inTubePosX-pathWidth + inVerticalWidth/2.0);
                pathCoords.push_back(inVerticalY + inVerticalHeight/2.0);
                
                pathCoords.push_back(downF);
                
                /*
                inVerticalXdot = inTubePosX-pathWidth - inVerticalWidth/2.0;
                inVerticalYdot = abs(inVerticalY - inVerticalHeight/2.0) + pathHeight;
                
                cout << "queue below center\n";
                 */
            }
            else if(currQueue.getY() < inTubePosY) { //queue is above center
                pathCoords.push_back(abs(inVerticalY - inVerticalHeight/2.0));
                pathCoords.push_back(inTubePosX-pathWidth + inVerticalWidth/2.0);
                pathCoords.push_back((inVerticalY + inVerticalHeight/2.0) - pathHeight);
            
                pathCoords.push_back(upF);
                
                /*
                inVerticalXdot = inTubePosX-pathWidth + inVerticalWidth/2.0;
                inVerticalYdot = ((inVerticalY + inVerticalHeight/2.0) - pathHeight);
                
                cout << "queue above center\n";
                 */
            }
            else {
                //Precondition of x, y in queue not satisfied.
                cout << "Error queue x, y precond not satisfied\n";
            }
        }
        
        /* For debugging errors related to pathCoordinates
        sf::CircleShape dot;
        dot.setFillColor(sf::Color::Blue);
        dot.setOutlineColor(lineOutlineColor);
        dot.setOutlineThickness(pathHeight/5.0);
        dot.setRadius(pathHeight);
        dot.setOrigin(pathHeight, pathHeight);
        dot.setPosition(inVerticalXdot, inVerticalYdot);
        cout << "X = " << inVerticalXdot << " Y = " << inVerticalYdot << ".\n";
        window->draw(dot);
         */
        
        if(currQueue.getY() > inTubePosY) { //queue is below center
            leftLinePosY -= VerticalAdjustmentY;
        }
        else if(currQueue.getY() < inTubePosY) { //queue is above center
            leftLinePosY += VerticalAdjustmentY;
        }
        
        sf::RectangleShape leftLine1;
        leftLine1.setFillColor(lineColor);
        leftLine1.setOutlineColor(lineOutlineColor);
        leftLine1.setOutlineThickness(pathHeight/5.0);
        leftLine1.setSize(sf::Vector2f(leftLine1Width, leftLine1Height));
        leftLine1.setOrigin(leftLine1Width/2.0, leftLine1Height/2.0);
        leftLine1.setPosition(abs(abs(inTubePosX-pathWidth) - leftLine1Width/2.0), leftLinePosY);
        window->draw(leftLine1);
        
        if(!pathStored) {
            pathCoords.push_back(abs(abs(inTubePosX-pathWidth) - leftLine1Width/2.0) - leftLine1Width/2.0);
            pathCoords.push_back(abs(leftLinePosY) - leftLine1Height/2.0);
            pathCoords.push_back((abs(inTubePosX-pathWidth) - leftLine1Width/2.0) + leftLine1Width/2.0);
            pathCoords.push_back(leftLinePosY + leftLine1Height/2.0);
            pathCoords.push_back(leftF);
        }
        
        sf::RectangleShape outVertical;
        outVertical.setFillColor(lineColor);
        outVertical.setOutlineColor(lineOutlineColor);
        outVertical.setOutlineThickness(pathHeight/5.0);
        outVertical.setSize(sf::Vector2f(outVerticalWidth, outVerticalHeight));
        outVertical.setOrigin(outVerticalWidth/2.0, outVerticalHeight/2.0);
        outVertical.setPosition(RES_X-(inTubePosX-pathWidth), inVerticalY);
        window->draw(outVertical);
        
        if(!pathStored) {
            pathCoords.push_back(RES_X-(inTubePosX-pathWidth) - outVerticalWidth/2.0);
            pathCoords.push_back(inVerticalY - outVerticalHeight/2.0);
            pathCoords.push_back(RES_X-(inTubePosX-pathWidth) + outVerticalWidth/2.0);
            pathCoords.push_back(inVerticalY + outVerticalHeight/2.0);
            if(currQueue.getY() >= RES_Y2) pathCoords.push_back(upF);
            else pathCoords.push_back(downF);
        }
        
        sf::RectangleShape leftLine2;
        leftLine2.setFillColor(lineColor);
        leftLine2.setOutlineColor(lineOutlineColor);
        leftLine2.setOutlineThickness(pathHeight/5.0);
        leftLine2.setSize(sf::Vector2f(leftLine2Width, leftLine2Height));
        leftLine2.setOrigin(leftLine2Width/2.0, leftLine2Height/2.0);
        leftLine2.setPosition(abs(abs(RES_X - (inTubePosX-pathWidth)) - leftLine2Width/2.0), leftLinePosY);
        window->draw(leftLine2);
        
        if(!pathStored) {
            pathCoords.push_back(abs(abs(RES_X - (inTubePosX-pathWidth)) - leftLine2Width/2.0));
            pathCoords.push_back(abs(currQueue.getHeight()/2.0 - currQueue.getY()) - leftLine2Height/2.0);
            pathCoords.push_back(abs(RES_X - (inTubePosX-pathWidth)) + leftLine2Width);
            pathCoords.push_back(abs(currQueue.getHeight()/2.0 - leftLinePosY) + leftLine2Height/2.0);
            pathCoords.push_back(leftF);
        }
    }
    //cout << "Queue paths drawn.\n";
}

void Level::drawStackPath() {
    float pathWidth = (ballsRadii.at(num)*25.0);
    float pathHeight = (ballsRadii.at(num)*2.0)/5.0; //inTube height/5.0
    
    //have to switch width and height to make vertical
    float inVerticalWidth = pathHeight;
    float inVerticalHeight = 0.0;
    float inVerticalY = inTubePosY;
    
    float leftLine1Width = 0.0;
    float leftLine1Height = pathHeight;
    
    float leftLine2Width = 0.0;
    float leftLine2Height = pathHeight;
    
    float outVerticalWidth = pathHeight;
    float outVerticalHeight = 0.0;
    
    for(int i=0; i<stacks.size(); i++) {
        tStack currStack = stacks.at(i);
        
        inVerticalHeight = abs(inTubePosY - abs(currStack.getY()-currStack.getHeight()/2.0));
        outVerticalHeight = abs((RES_Y-inTubePosY) - abs(currStack.getY()-currStack.getHeight()/2.0));
        
        if(currStack.getY() > inTubePosY) inVerticalY = abs(inTubePosY+(inVerticalHeight/2.0));
        else inVerticalY = abs(inTubePosY-(inVerticalHeight/2.0));
        
        leftLine1Width = abs(currStack.getX() - (inTubePosX-pathWidth));
        leftLine2Width = ((RES_X - (inTubePosX-pathWidth)) - currStack.getX());
        
        sf::RectangleShape inVertical;
        inVertical.setFillColor(lineColor);
        inVertical.setOutlineColor(lineOutlineColor);
        inVertical.setOutlineThickness(pathHeight/5.0);
        inVertical.setSize(sf::Vector2f(inVerticalWidth, inVerticalHeight));
        inVertical.setOrigin(inVerticalWidth/2.0, inVerticalHeight/2.0);
        inVertical.setPosition(inTubePosX-pathWidth, inVerticalY);
        window->draw(inVertical);
        
        if(!pathStored) {
            pathCoords.push_back(inTubePosX-pathWidth - inVerticalWidth/2.0);
            if(currStack.getY() > inTubePosY) { //stack is below center
                pathCoords.push_back(abs(inVerticalY - inVerticalHeight/2.0) + pathHeight);
                pathCoords.push_back(inTubePosX-pathWidth + inVerticalWidth/2.0);
                pathCoords.push_back(inVerticalY + inVerticalHeight/2.0);
                
                pathCoords.push_back(downF);
                
                /*
                inVerticalXdot = inTubePosX-pathWidth - inVerticalWidth/2.0;
                inVerticalYdot = (inVerticalY - inVerticalHeight/2.0) + pathHeight;
                 */
            }
            else if(currStack.getY() < inTubePosY) { //stack is above center
                pathCoords.push_back(abs(inVerticalY - inVerticalHeight/2.0));
                pathCoords.push_back(inTubePosX-pathWidth + inVerticalWidth/2.0);
                pathCoords.push_back((inVerticalY + inVerticalHeight/2.0) - pathHeight);
            
                pathCoords.push_back(upF);
                
                /*
                inVerticalXdot = inTubePosX-pathWidth + inVerticalWidth/2.0;
                inVerticalYdot = (inVerticalY + inVerticalHeight/2.0) - pathHeight;
                 */
            }
            else {
                //Precondition of x, y in queue not satisfied.
            }
        }
        
        /* For debugging errors related to pathCoordinates
        sf::CircleShape dot;
        dot.setFillColor(sf::Color::Red);
        dot.setOutlineColor(lineOutlineColor);
        dot.setOutlineThickness(pathHeight/5.0);
        dot.setRadius(pathHeight);
        dot.setOrigin(pathHeight, pathHeight);
        dot.setPosition(inTubePosX-pathWidth - inVerticalWidth/2.0, abs(inVerticalY - inVerticalHeight/2.0) + pathHeight);
        window->draw(dot);
        */
        
        sf::RectangleShape leftLine1;
        leftLine1.setFillColor(lineColor);
        leftLine1.setOutlineColor(lineOutlineColor);
        leftLine1.setOutlineThickness(pathHeight/5.0);
        leftLine1.setSize(sf::Vector2f(leftLine1Width, leftLine1Height));
        leftLine1.setOrigin(leftLine1Width/2.0, leftLine1Height/2.0);
        leftLine1.setPosition(abs(abs(inTubePosX-pathWidth) - leftLine1Width/2.0), abs(currStack.getHeight()/2.0 - currStack.getY()));
        window->draw(leftLine1);
        
        if(!pathStored) {
        pathCoords.push_back(abs(abs(inTubePosX-pathWidth) - leftLine1Width/2.0) - leftLine1Width/2.0);
        pathCoords.push_back(abs(currStack.getHeight()/2.0 - currStack.getY()) - leftLine1Height/2.0);
        pathCoords.push_back(abs(abs(inTubePosX-pathWidth) - leftLine1Width/2.0) + leftLine1Width/2.0);
        pathCoords.push_back(abs(currStack.getHeight()/2.0 - currStack.getY()) + leftLine1Height/2.0);
        pathCoords.push_back(leftF);
        }
        
        sf::RectangleShape outVertical;
        outVertical.setFillColor(lineColor);
        outVertical.setOutlineColor(lineOutlineColor);
        outVertical.setOutlineThickness(pathHeight/5.0);
        outVertical.setSize(sf::Vector2f(outVerticalWidth, outVerticalHeight));
        outVertical.setOrigin(outVerticalWidth/2.0, outVerticalHeight/2.0);
        outVertical.setPosition(RES_X-(inTubePosX-pathWidth), inVerticalY);
        window->draw(outVertical);

        if(!pathStored) {
        pathCoords.push_back(RES_X-(inTubePosX-pathWidth) - outVerticalWidth/2.0);
        pathCoords.push_back(inVerticalY - outVerticalHeight/2.0);
        pathCoords.push_back(RES_X-(inTubePosX-pathWidth) + outVerticalWidth/2.0);
        pathCoords.push_back(inVerticalY + outVerticalHeight/2.0);
        if(currStack.getY() >= RES_Y2) pathCoords.push_back(upF);
        else pathCoords.push_back(downF);
        }
        
        sf::RectangleShape leftLine2;
        leftLine2.setFillColor(lineColor);
        leftLine2.setOutlineColor(lineOutlineColor);
        leftLine2.setOutlineThickness(pathHeight/5.0);
        leftLine2.setSize(sf::Vector2f(leftLine2Width, leftLine2Height));
        leftLine2.setOrigin(leftLine2Width/2.0, leftLine2Height/2.0);
        leftLine2.setPosition(abs(abs(RES_X - (inTubePosX-pathWidth)) - leftLine2Width/2.0), abs(currStack.getHeight()/2.0 - currStack.getY()));
        window->draw(leftLine2);
        
        if(!pathStored) {
        pathCoords.push_back(abs(abs(RES_X - (inTubePosX-pathWidth)) - leftLine2Width/2.0));
        pathCoords.push_back(abs(currStack.getHeight()/2.0 - currStack.getY()) - leftLine2Height/2.0);
        pathCoords.push_back(abs(abs(RES_X - (inTubePosX-pathWidth)) + leftLine2Width));
        pathCoords.push_back(abs(currStack.getHeight()/2.0 - currStack.getY()) + leftLine2Height/2.0);
        pathCoords.push_back(leftF);
        }
    }
    //cout << "Stack paths drawn.\n";
}

void Level::drawLevel() {
    std::vector<int> toppedBallsID;
    
    drawLevelBar();
    drawInTube();
    drawOutTube();
    
    drawStandardPath();
    drawQueuePath();
    drawStackPath();
    pathStored = true;
    
    //balls drawn after tubes makes tubes transparent
    for(int i=0; i<balls.size(); i++) {
        if(balls.at(i).isTopped) toppedBallsID.push_back(i);
        else balls.at(i).draw();
    }
    
    for(int i=0; i<queues.size(); i++) {
        queues.at(i).draw();
    }
    for(int i=0; i<stacks.size(); i++) {
        stacks.at(i).draw();
    }
    
    //draw topped or fronted balls on top of stacks and queues so that they are seen
    for(int i=0; i<toppedBallsID.size(); i++) {
        balls.at(toppedBallsID.at(i)).draw();
    }
}

void Level::clearLevel() {
    pathCoords.clear();
    balls.clear();
    queues.clear();
    stacks.clear();
}