#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <string>
#include <time.h>
using namespace std;

/// Globals
sf::RenderWindow* window;
float RES_X = 1200;
float RES_Y = 800;
float RES_Y2 = RES_Y/2;

class Ball {
private:
    float x, y;
    float vx, vy; //vx is (pixels per second/framerate) eg. if vx is 0.5 and framerate is 60 then the speed of this object in pixels per second is 30px/s
    float radius = 10;
    float dia;
    
    sf::Color color;
    sf::String label; //text on the ball, typically a single character
    
public:
    bool isActive;
    bool isMoving;
    bool isOnScreen;
    
    Ball(float x, float y, float vx, float vy, float radius, sf::Color color, sf::String label) {
        this->x = x;
        this->y = y;
        this->vx = vx;
        this->vy = vy;
        this->radius = radius;
        this->color = color;
        this->label = label;
        
        dia = radius*2;
        isActive = true;
        isMoving = false;
    }
    
    bool checkOnScreen() {
        if (x < -(radius) || y < -(radius) || x > RES_X + x || y > RES_Y + y) {
            return false;
        }
        return true;
    }
    
    void update(bool status) {
        isOnScreen = checkOnScreen();
        
        isMoving = status;
        if(!isMoving || !isActive) return;
        x -= vx;
        if (x < -(dia) ||
            y < -(dia)) isActive = false;
    }
    
    void draw() {
        if(!isOnScreen || !isActive) return;
        
        sf::CircleShape ballCircle;
        ballCircle.setFillColor(color);
        ballCircle.setRadius(radius);
        ballCircle.setPosition(x, y);
        ballCircle.setOrigin(radius, radius);
        
        //place label on ball
        // Declare and load a font
        sf::Font ballFont;
        ballFont.loadFromFile("/Users/ravi/Documents/Orbital/Stacks and Queues/Stacks and Queues/sansation.ttf");
        // Create a text
        sf::Text ballText(label, ballFont);
        ballText.setCharacterSize(dia);
        ballText.setStyle(sf::Text::Bold);
        ballText.setColor(sf::Color::White);
        //ballText.setOrigin(x+radius, y+radius);
        ballText.setPosition(x-(radius/1.50), y-(radius/0.75));
        
        window->draw(ballCircle);
        window->draw(ballText);
    }
};

class Level {
private:
    std::vector<float> ballsPositionX { RES_X, RES_X , RES_X};
    std::vector<float> ballsPositionY { RES_Y2, RES_Y2, RES_Y };
    std::vector<float> ballsPeriod { 2.0, 2.0, 2.0 }; //balls appear on screen every x seconds
    std::vector<float> ballsVX { 1.0, 1.0, 1.0 }; //respective vx of balls in a level by level number
    std::vector<float> ballsRadii { 10, 10, 10 };
    
public:
    int num;
    bool isActive;
    bool domino; //when the level starts, the movement of the first ball triggers the movement of the rest at constant intervals
    
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
        return (((float)interval)/CLOCKS_PER_SEC);
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
                    cout << getInterval();
                    if(getInterval() >= ballsPeriod.at(i-1)) {
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
        
    }
};

Level* level1;
std::vector<Level> levels;

void initialiseLevel1() {
    
    level1 = new Level(1);
    levels.push_back(*level1);
    
    //get level info
    float x = level1->getBallPositionX();
    float y = level1->getBallPositionY();
    float vx1 = level1->getBallVX();
    float vy1 = vx1;
    float period = level1->getBallPeriod();
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

void initialiseMainMenu() {
    //for a start, it says something like 'press enter to play'
}

void initialiseGame() {
    initialiseMainMenu();
    initialiseLevel1();
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

void processEvent(sf::Event& event) {
    switch(event.type) {
            
        case sf::Event::Closed: {
            window->close();
            break;
        }
        default: ; //nothing
    }
}

int main() {
    window = new sf::RenderWindow(sf::VideoMode(RES_X, RES_Y), "Stacks and Queues");
    
    sf::Clock clock;
    float frameTime = 1/60.0f;
    float dTime = 0;
    
    
    initialiseGame();
    
    while (window->isOpen()) {
        dTime += clock.getElapsedTime().asSeconds();
        clock.restart();
        
        // Event handling
        sf::Event event;
        while(window->pollEvent(event)) {
            processEvent(event);
        }
        
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
    }
    
    //read somewhere that it was good c++ practice to delete all objects once they're out of scope
    
    delete window;
    return 0;
}
