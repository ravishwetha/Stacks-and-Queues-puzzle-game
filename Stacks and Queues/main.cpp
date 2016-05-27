
#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>
#include <string>

/// Globals
sf::RenderWindow* window;
int RES_X = 800;
int RES_Y = 600;

class Ball {
private:
    int x, y;
    float vx, vy;
    
public:
    
    float radius = 10;
    float dia;
    int period; //a new ball appears every x seconds on screen
    
    sf::Color color;
    sf::String label; //text on the ball, typically a single character
    
    bool isActive;
    
    Ball(int x, int y, float vx, float vy, float radius, int period, sf::Color color, sf::String label) {
        this->x = x;
        this->y = y;
        this->vx = vx;
        this->vy = vy;
        this->radius = radius;
        this->period = period;
        this->color = color;
        this->label = label;
        
        dia = radius*2;
        isActive = true;
    }
    
    void update() {
        if(!isActive) return;
        x -= vx;
        if (x < -dia || x > RES_X + dia ||
            y < -dia || y > RES_Y + dia) isActive = false;
    }
    
    void draw() {
        sf::CircleShape shape;
        shape.setFillColor(sf::Color::Red);
        shape.setRadius(radius);
        shape.setPosition(x, y);
        
        
        //place label on ball
        // Declare and load a font
        sf::Font font;
        font.loadFromFile("arial.ttf");
        // Create a text
        sf::Text text(label, font);
        text.setCharacterSize(30);
        text.setStyle(sf::Text::Bold);
        text.setColor(sf::Color::White);
        
        text.setPosition(x, y);
        
        
        window->draw(shape);
        //window->draw(text);
    }
};

Ball* ball;

class Level {
    
};

void initialiseGame() {
    ball = new Ball(800, 300, 0.5, 0.5, 10, 10, sf::Color::Red, "3");
}

void updateGame() {
    ball->update();
}

void drawGameFrame() {
    ball->draw();
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