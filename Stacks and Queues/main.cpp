//Stacks and Queues
//Copyright © 2016 TeamSQ. All rights reserved.

//main.cpp

#include "Ball.hpp"

///Globals
sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(RES_X, RES_Y), "Stacks and Queues");
float RES_X = 1200;
float RES_Y = 800;
float RES_Y2 = RES_Y/2;

class Level {
private:
    std::vector<float> ballsPositionX { RES_X, RES_X , RES_X};
    std::vector<float> ballsPositionY { RES_Y2, RES_Y2, RES_Y };
    std::vector<float> ballsPeriod { 1.0, 2.0, 2.0 }; //balls appear on screen every x seconds
    std::vector<float> ballsVX { 1.0, 1.0, 1.0 }; //respective vx of balls in a level by level number
    std::vector<float> ballsRadii { 10, 10, 10 };
    
public:
    int num;
    bool isActive;
    
    //objects in level
    clock_t ballClock;
    std::vector<Ball> balls;
    
    Level(int num) {
        this->num = num;
        isActive = true;
    }
    
    float getBallPositionX() {
        return ballsPositionX.at(num);
    }
    
    float getBallPositionY() {
        return ballsPositionY.at(num);
    }
    
    float getBallVX() {
        return ballsVX.at(num);
    }
    
    float getBallPeriod() {
        return ballsPeriod.at(num);
    }
    
    float getBallRadius() {
        return ballsRadii.at(num);
    }
    
    void startBallClock() {
        ballClock = clock();
    }
    
    float getInterval() {
        clock_t interval;
        interval = clock() - ballClock;
        return (((float)interval)/(CLOCKS_PER_SEC))*6;
    }
    
    void updateLevel() {
        
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
    void drawInTube() {
        float width = (ballsRadii.at(num)*2)*3; //can hold three balls at a time
        float height = ballsRadii.at(num)*2;
        sf::RectangleShape inTube;
        inTube.setFillColor(sf::Color::White);
        inTube.setSize(sf::Vector2f(width, height));
        inTube.setPosition(RES_X-width/2.0, RES_Y2);
        inTube.setOrigin(width/2.0, height/2.0);
        window->draw(inTube);
    }
    
    void drawOutTube() {
        //TO-DO
    }
    
    void drawLevel() {
        drawInTube();
        drawOutTube();
        for( int i = 0; i < balls.size(); i = i + 1 ) {
            balls.at(i).draw();
        }
    }
    
    //once all balls are off screen
    void clearLevel() {
        //TO-DO
    }
};

Level* level1;
std::vector<Level> levels;

bool key_return; //start game
bool key_P; //pause game
bool key_escape; //reset game

void keyDown(sf::Keyboard::Key keyCode) {
    switch(keyCode) {
        case sf::Keyboard::Return: key_return = true; break;
        case sf::Keyboard::Escape: key_escape = true; break;
        case sf::Keyboard::P: key_P = true; break;
        default: ;
    }
}

void keyUp(sf::Keyboard::Key keyCode) {
    switch(keyCode) {
        case sf::Keyboard::Return: key_return = false; break;
        case sf::Keyboard::Escape: key_escape = false; break;
        case sf::Keyboard::P: key_P = false; break;
        default: ;
    }
}

void processEvent(sf::Event& event) {
    switch(event.type) {
        case sf::Event::Closed: {
            window->close();
            break;
        }
        case sf::Event::KeyPressed: {
            keyDown(event.key.code);
            break;
        }
        case sf::Event::KeyReleased: {
            keyUp(event.key.code);
            break;
        }
        default: ; //nothing
    }
}

void initialiseLevel1() {
    
    level1 = new Level(1);
    levels.push_back(*level1);
    
    //get level info
    float x = level1->getBallPositionX();
    float y = level1->getBallPositionY();
    float vx1 = level1->getBallVX();
    float vy1 = vx1;
    float radius = level1->getBallRadius();
    
    //create level objects accordingly
    Ball lvl1ball1 = Ball(x - (radius*5), y, vx1, vy1, radius, sf::Color::Red, "1");
    Ball lvl1ball3 = Ball(x - (radius*3), y, vx1, vy1, radius, sf::Color::Red, "3");
    Ball lvl1ball4 = Ball(x - (radius), y, vx1, vy1, radius, sf::Color::Red, "4");
    
    //store objects in level
    level1->balls.push_back(lvl1ball1);
    level1->balls.push_back(lvl1ball3);
    level1->balls.push_back(lvl1ball4);
}

void runMainMenu() {
    //TO-DO
    //for a start, it says something like 'press enter to play'
    window->clear();
    window->display();
}

void runPauseScreen() {
    //TO-DO
    //just says 'paused'
    window->clear();
    window->display();
}

void updateGame() {
    
    //level1
    if(level1->isActive) {
        level1->updateLevel();
    }
}

void drawGameFrame() {
    
    //level1
    if(level1->isActive) {
        level1->drawLevel();
    }
}

void initialiseGame() {
    initialiseLevel1();
}

int main() {
    bool gameRunning = false;
    bool gameNotPaused = true;
    
    sf::Clock clock;
    float frameTime = 1/60.0f;
    float dTime = 0;
    
    initialiseGame();
    
    while (window->isOpen()) {
        
        // Event handling
        sf::Event event;
        while(window->pollEvent(event)) {
            processEvent(event);
            if(key_return) {
                //cout << "Return key pressed.\n";
                gameRunning = true;
                gameNotPaused = true;
            }
        }
    
        if(gameRunning && gameNotPaused) {
            
            dTime += clock.getElapsedTime().asSeconds();
            clock.restart();
            
            // Safeguard (slowdown) to prevent game from lagging to death
            if (dTime > 5*frameTime) dTime = 5*frameTime;
            
            // Update game
            while (dTime > frameTime) {
                dTime -= frameTime;
                updateGame();
            }
            
            // Draw frame
            window->clear();
            drawGameFrame();
            window->display();
            
            //cout << "Game is running.\n";
            while(window->pollEvent(event)) {
                processEvent(event);
                if(key_escape) {
                    //cout << "Escape key pressed.\n";
                    gameRunning = false;
                }
                if(key_P) {
                    //cout << "P key pressed.\n";
                    gameNotPaused = false;
                }
            }
        }
        
        //'P' key to pause game by making gameRunning false
        else if(gameRunning && !gameNotPaused) {
            //cout << "Game is paused.\n";
            runPauseScreen();
        }
        
        //'Escape' go to msin menu and reset game //It currently only pauses the game
        else if(!gameRunning) {
            runMainMenu();
        }
    }
    
    //read somewhere that it was good c++ practice to delete all objects once they're out of scope, I don't think there is a garbage collector like in Java
    
    delete window;
    return 0;
}
