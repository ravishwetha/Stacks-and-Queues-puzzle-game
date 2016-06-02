//Stacks and Queues
//Copyright © 2016 TeamSQ. All rights reserved.

//main.cpp

#include "Level.hpp"

///Globals
float RES_X = 1200;
float RES_Y = 800;
float RES_Y2 = RES_Y/2.0;
sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(RES_X, RES_Y), "Stacks and Queues");

//Window
sf::Color backgroundColor = sf::Color::White;

//Game
std::vector<Level> levels;
Level* level1;

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
    level1 = new Level(0);
    levels.push_back(*level1);
    
    //cout << "Created level object.\n";
    
    //get level info
    float x = level1->getInTubePositionX();
    float y = level1->getInTubePositionY();
    float vx1 = level1->getBallVX();
    float vy1 = vx1;
    float radius = level1->getBallRadius();
    
    
    //cout << "Level 1 variables initialised.\n";
    
    //create level objects accordingly
    Ball lvl1ball1 = Ball(x - (radius*5), y, vx1, vy1, radius, sf::Color::Red, "1");
    Ball lvl1ball3 = Ball(x - (radius*3), y, vx1, vy1, radius, sf::Color::Red, "3");
    Ball lvl1ball4 = Ball(x - (radius), y, vx1, vy1, radius, sf::Color::Red, "4");
    
    tStack lvl1stack1 = tStack(600, 200, radius*2, radius*6);
    
    //cout << "Level 1 objects initialised.\n";
    
    //store objects in level
    level1->balls.push_back(lvl1ball1);
    level1->balls.push_back(lvl1ball3);
    level1->balls.push_back(lvl1ball4);
    
    level1->stacks.push_back(lvl1stack1);
    
    //cout << "Level 1 vectors initialised.\n";

}

void initialiseGame() {
    //cout << "about to initialise lvl 1.\n";
    initialiseLevel1();
}

void runMainMenu() {
    //TODO: for a start, it says something like 'press enter to play'
    window->clear();
    window->display();
}

void runPauseScreen() {
    //TODO: just says 'paused' and you can still see the level under the word
    window->clear();
    window->display();
}

void updateGame() {
    if(level1->isActive) {
        level1->updateLevel();
    }
}

void drawGameFrame() {
    if(level1->isActive) {
        level1->drawLevel();
    }
}

int main() {
    
    bool gameRunning = false;
    bool gameNotPaused = true;
    
    sf::Clock clock;
    float frameTime = 1/60.0f;
    float dTime = 0;
    
    //cout << "Main.\n";
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
            //window->clear();
            window->sf::RenderTarget::clear(backgroundColor);
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
        
        //'Escape' go to main menu and reset game //It currently only pauses the game
        else if(!gameRunning) {
            runMainMenu();
        }
    }
    
    //read somewhere that it was good c++ practice to delete all objects once they're out of scope, I don't think there is a garbage collector like in Java
    
    delete window;
    return 0;
}
