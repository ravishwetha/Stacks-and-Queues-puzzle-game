
#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <string>

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
    }
    
    void update() {
        if(!isActive) return;
        x -= vx;
        if (x < -(dia) ||
            y < -(dia)) isActive = false;
    }
    
    void draw() {
        sf::CircleShape ballCircle;
        ballCircle.setFillColor(color);
        ballCircle.setRadius(radius);
        ballCircle.setPosition(x, y);
        //shape.setOrigin(radius, radius);
        
        //place label on ball
        // Declare and load a font
        sf::Font ballFont;
        ballFont.loadFromFile("/Users/ravi/Documents/Orbital/Stacks and Queues/Stacks and Queues/sansation.ttf");
        // Create a text
        sf::Text ballText(label, ballFont);
        ballText.setCharacterSize(dia);
        ballText.setStyle(sf::Text::Bold);
        ballText.setColor(sf::Color::White);
        ballText.setPosition(x+dia/5, y-dia/10);
        
        
        window->draw(ballCircle);
        window->draw(ballText);
    }
};

Ball* lvl1ball1;
Ball* lvl1ball3;
Ball* lvl1ball4;

class Level {
private:
    std::vector<float> ballsPositionX { RES_X, RES_X };
    std::vector<float> ballsPositionY { RES_Y2, RES_Y2 };
    std::vector<float> ballsVX { RES_X/1000, RES_X/1000 }; //respective vx of balls in a level by level number
    std::vector<float> ballsPeriod { 2.0, 4.9 }; //balls appear on screen every x seconds
    std::vector<float> ballsRadii { 10, 10 };
    
public:
    int num;
    bool isActive;
    
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
    
    void drawInTube() {
        float width = ballsRadii.at(num)*4;
        float height = ballsRadii.at(num)*2;
        sf::RectangleShape inTube;
        inTube.setFillColor(sf::Color::White);
        inTube.setSize(sf::Vector2f(width, height));
        inTube.setOrigin(ballsPositionX.at(num) - width, ballsPositionY.at(num) + (height/2));
        inTube.setPosition(ballsPositionX.at(num), ballsPositionY.at(num));
        window->draw(inTube);
    }

};

Level* level1;
std::vector<Level> levels;

void initialiseLevel1() {
    
    level1 = new Level(1);
    levels.push_back(*level1);
    
    float x = level1->getBallPositionX();
    float y = level1->getBallPositionY();
    float vx1 = level1->getBallVX();
    float period = level1->getBallPeriod();
    float xPixInterval = vx1*12*period;
    float radius = level1->getBallRadius();
    
    lvl1ball1 = new Ball(x, y, vx1, 0.5, radius, sf::Color::Red, "1");
    lvl1ball3 = new Ball(x + xPixInterval, y, vx1, 0.5, radius, sf::Color::Red, "3");
    lvl1ball4 = new Ball(x + xPixInterval*2, y, vx1, 0.5, radius, sf::Color::Red, "4");
}

void initialiseGame() {
    initialiseLevel1();
}

void updateGame() {
    
    //level1
    if(level1->isActive) {
       lvl1ball1->update();
       lvl1ball3->update();
       lvl1ball4->update();
    }
}

void drawGameFrame() {
    
    //level1
    if(level1->isActive) {
        level1->drawInTube();
        lvl1ball1->draw();
        lvl1ball3->draw();
        lvl1ball4->draw();
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
    
    delete window;
    return 0;
}
