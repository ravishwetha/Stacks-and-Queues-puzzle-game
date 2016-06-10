//Stacks and Queues
//Copyright © 2016 TeamSQ. All rights reserved.

//main.cpp

//#include "SplashScreen.h"
#include "MainMenu.h"
#include "Level.hpp"

///Globals
float RES_X = 1200;
float RES_Y = 800;
float RES_Y2 = RES_Y/2.0;
sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(RES_X, RES_Y), "Stacks and Queues");

//Window
sf::Color backgroundColor = sf::Color::White;

//Game
int ballIndex = 0;
Level* currLevel;
Level* level1;

bool key_return; //start game
bool key_escape; //reset game
bool key_P; //pause game

//change ball direction
bool key_up;
bool key_down;

//change selected ball
bool key_left;
bool key_right;

void keyDown(sf::Keyboard::Key keyCode) {
    switch(keyCode) {
        case sf::Keyboard::Return: key_return = true; break;
        case sf::Keyboard::Escape: key_escape = true; break;
        case sf::Keyboard::P: key_P = true; break;
        case sf::Keyboard::Up: key_up = true; break;
        case sf::Keyboard::Down: key_down = true; break;
        case sf::Keyboard::Left: key_left = true; break;
        case sf::Keyboard::Right: key_right = true; break;
        default: ;
    }
}

void keyUp(sf::Keyboard::Key keyCode) {
    switch(keyCode) {
        case sf::Keyboard::Return: key_return = false; break;
        case sf::Keyboard::Escape: key_escape = false; break;
        case sf::Keyboard::P: key_P = false; break;
        case sf::Keyboard::Up: key_up = false; break;
        case sf::Keyboard::Down: key_down = false; break;
        case sf::Keyboard::Left: key_left = false; break;
        case sf::Keyboard::Right: key_right = false; break;
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
    
    //cout << "Created level object.\n";
    
    //get level info
    float x = level1->getInTubePositionX();
    float y = level1->getInTubePositionY();
    float vx1 = level1->getBallVX();
    float vy1 = vx1;
    float radius = level1->getBallRadius();
    
    //cout << "Level 1 variables initialised.\n";
    
    //create level objects accordingly
    Ball lvl1ball1 = Ball(0, x - (radius*5), y, vx1, vy1, radius, sf::Color::Red, "1");
    Ball lvl1ball3 = Ball(1, x - (radius*3), y, vx1, vy1, radius, sf::Color::Red, "3");
    Ball lvl1ball4 = Ball(2, x - (radius), y, vx1, vy1, radius, sf::Color::Red, "4");
    
    tStack lvl1stack1 = tStack(600, 600, radius*2, radius*6);
    
    //cout << "Level 1 objects initialised.\n";
    
    //store objects in level
    level1->balls.push_back(lvl1ball1);
    level1->balls.push_back(lvl1ball3);
    level1->balls.push_back(lvl1ball4);
    
    level1->stacks.push_back(lvl1stack1);
    
    //cout << "Level 1 vectors initialised.\n";
    
    ballIndex = 0;
    currLevel = level1;
}

void initialiseGame() {
    initialiseLevel1();
}

void backupMainMenu() {
    window->clear();
    
    sf::Font titleFont;
    titleFont.loadFromFile("sansation.ttf"); //insert path to ttf sansation file
    
    sf::Text titleText("Stacks and Queues", titleFont);
    titleText.setCharacterSize(RES_X/25.0);
    titleText.setStyle(sf::Text::Bold);
    titleText.setColor(sf::Color::White);
    titleText.setPosition(RES_X/2 - titleText.getLocalBounds().width/2.0, (RES_Y*(0.45)) - titleText.getLocalBounds().height/2.0);
    window->draw(titleText);
    
    
    //Press enter to play
    sf::Font enterFont;
    enterFont.loadFromFile("sansation.ttf"); //insert path to ttf sansation file
    
    sf::Text enterText("Click Title to play", enterFont);
    enterText.setCharacterSize(RES_X/50.0);
    enterText.setStyle(sf::Text::Bold);
    enterText.setColor(sf::Color::White);
    enterText.setPosition(RES_X/2 - enterText.getLocalBounds().width/2.0, (RES_Y*(0.55)) - enterText.getLocalBounds().height/2.0);
    window->draw(enterText);
    
    window->display();
}

void clear() {
    currLevel->clearLevel();
}

void updateGame() {
    currLevel->updateLevel();
}

void drawGameFrame() {
    currLevel->drawLevel();
}

int main() {
    bool reinitialise = false;
    bool gameRunning = false;
    bool gameNotPaused = true;
    
    sf::Clock clock;
    float frameTime = 1/60.0f;
    float dTime = 0;
    
    //SplashScreen splashscreen;
    MainMenu mainmenu;
    initialiseGame();
    
    sf::Event event;
    while (window->isOpen()) {
        if(reinitialise) {
            initialiseGame();
            reinitialise = false;
        }
        
        if(!gameRunning) {
            //pressed escape
            clear();
            window->clear();
            switch(mainmenu.Show(*window)) {
                case MainMenu::MenuResult::Backup: backupMainMenu(); break;
                case MainMenu::MenuResult::Exit: window->close(); break;
                case MainMenu::MenuResult::Play: gameRunning = true; gameNotPaused = true; break;
                case MainMenu::MenuResult::Nothing: ;
                default: ;
            }
            reinitialise = true;
        }
        
        else if(gameRunning && !gameNotPaused) {
            //cout << "Game is paused.\n";
            
            while(window->pollEvent(event)) {
                processEvent(event);
                if(key_escape) {
                    //cout << "Escape key pressed.\n";
                    gameRunning = false;
                    gameNotPaused = true;
                }
                else if(key_return) {
                    //cout << "Return key pressed.\n";
                    gameRunning = true;
                    gameNotPaused = true;
                }
            }
        }
        
        //PLAYING GAME
        else if(gameRunning && gameNotPaused) {
            
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
            window->sf::RenderTarget::clear(backgroundColor);
            drawGameFrame();
            window->display();
            
            //cout << "Game is running.\n";
            ballIndex = currLevel->selectedBall;
            while(window->pollEvent(event)) {
                processEvent(event);
                if(key_escape) {
                    //cout << "Escape key pressed.\n";
                    gameRunning = false;
                    gameNotPaused = true;
                    key_escape = false;
                }
                else if(key_P) {
                    //cout << "P key pressed.\n";
                    gameRunning = true;
                    gameNotPaused = false;
                }
                //else if(key_up) currLevel->balls.at(ballIndex).changeDirection(2);
                //else if(key_down) currLevel->balls.at(ballIndex).changeDirection(3);
                else if(key_left) currLevel->prevBall();
                else if(key_right) currLevel->nextBall();
            }
        }
    }
    
    clear();
    delete window;
    return 0;
}
