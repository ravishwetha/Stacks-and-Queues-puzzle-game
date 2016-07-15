//Stacks and Queues
//Copyright © 2016 TeamSQ. All rights reserved.

//main.cpp

//#include "SplashScreen.h"
#include "MainMenu.h"
#include "Level.hpp"

///Globals
std::string rPath = resourcePath();
float RES_X = 1200;
float RES_Y = 800;
float RES_Y2 = RES_Y/2.0;
sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(RES_X, RES_Y), "Stacks and Queues");

std::vector<float> pathCoords;
float leftF = 1.0;
float upF = 2.0;
float downF = 3.0;

std::vector<float> inTubePositionX = { RES_X, RES_X , RES_X };
std::vector<float> inTubePositionY = { RES_Y2, RES_Y2, RES_Y };
std::vector<float> ballsPeriod = { 5.0, 2.0, 2.0 };
std::vector<float> ballsVX = { 1.0, 1.0, 1.0 };
std::vector<float> ballsRadii = { 10, 10, 10 };

//Window
sf::Color backgroundColor = sf::Color::White;

//Game
int ballIndex = 0;
Level* currLevel;
Level* level1;

bool key_return = false; //start game
bool key_escape = false;//reset game
bool key_P = false; //pause game

//change ball direction
bool key_W = false;
bool key_S = false;
bool key_A = false;
//no key_D since balls can't go right

//change selected ball
bool key_Q = false;
bool key_E = false;

//select stack or queue
bool mouse_left = false;
bool mouse_right = false;
float mouse_X = 0.0;
float mouse_Y = 0.0;

void keyDown(sf::Keyboard::Key keyCode) {
    switch(keyCode) {
        case sf::Keyboard::Return: key_return = true; break;
        case sf::Keyboard::Escape: key_escape = true; break;
        case sf::Keyboard::P: key_P = true; break;
        case sf::Keyboard::W: key_W = true; break;
        case sf::Keyboard::S: key_S = true; break;
        case sf::Keyboard::A: key_A = true; break;
        case sf::Keyboard::Q: key_Q = true; break;
        case sf::Keyboard::E: key_E = true; break;
        default: ;
    }
}

void keyUp(sf::Keyboard::Key keyCode) {
    switch(keyCode) {
        case sf::Keyboard::Return: key_return = false; break;
        case sf::Keyboard::Escape: key_escape = false; break;
        case sf::Keyboard::P: key_P = false; break;
        case sf::Keyboard::W: key_W = false; break;
        case sf::Keyboard::S: key_S = false; break;
        case sf::Keyboard::A: key_A = false; break;
        case sf::Keyboard::Q: key_Q = false; break;
        case sf::Keyboard::E: key_E = false; break;
        default: ;
    }
}

void mouseDown(sf::Mouse::Button mouseCode) {
    //cout << "mouseDown.\n";
    switch(mouseCode) {
        case sf::Mouse::Left: mouse_left = true; break;
        case sf::Mouse::Right: mouse_right = true; break;
        default: cout << "mouseCode error.\n";
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
        case sf::Event::MouseButtonPressed: {
            mouse_X = event.mouseButton.x;
            mouse_Y = event.mouseButton.y;
            cout << "from main.cpp: x = " << mouse_X << " y = " << mouse_Y << ".\n";
            mouseDown(event.mouseButton.button);
        }
        default: ; //nothing
    }
}

void initialiseLevel1() {
    std::vector<string> winOrder = {"3", "1", "4"};
    level1 = new Level(0, winOrder); //num is (level number - 1)
    
    //get level info
    float x = level1->getInTubePositionX();
    float y = level1->getInTubePositionY();
    float vx1 = level1->getBallVX();
    float vy1 = vx1*3;
    float radius = level1->getBallRadius();
    
    //create level objects accordingly
    Ball lvl1ball1 = Ball(0, x - (radius*5), y, vx1, vy1, radius, sf::Color::Red, "1");
    Ball lvl1ball3 = Ball(1, x - (radius*3), y, vx1, vy1, radius, sf::Color::Red, "3");
    Ball lvl1ball4 = Ball(2, x - (radius), y, vx1, vy1, radius, sf::Color::Red, "4");
    
    tStack lvl1stack1 = tStack(RES_X*(0.50), RES_Y*(0.60), radius*2, radius*6);
    tQueue lvl1queue1 = tQueue(RES_X*(0.50), RES_Y*(0.40), radius*6, radius*2);
    
    //cout << "Level 1 objects initialised.\n";
    
    //store objects in level
    level1->balls.push_back(lvl1ball1);
    level1->balls.push_back(lvl1ball3);
    level1->balls.push_back(lvl1ball4);
    
    level1->stacks.push_back(lvl1stack1);
    level1->queues.push_back(lvl1queue1);
    
    //cout << "Level 1 vectors initialised.\n";
    
    ballIndex = 0;
    currLevel = level1;
    
    cout << "Level 1 initialised.\n";
}

void initialiseGame() {
    initialiseLevel1();
}

void backupMainMenu() {
    window->clear();
    
    sf::Font titleFont;
    titleFont.loadFromFile(rPath + "sansation.ttf");
    sf::Text titleText("Stacks and Queues", titleFont);
    titleText.setCharacterSize(RES_X/25.0);
    titleText.setStyle(sf::Text::Bold);
    titleText.setColor(sf::Color::White);
    titleText.setPosition(RES_X/2 - titleText.getLocalBounds().width/2.0, (RES_Y*(0.45)) - titleText.getLocalBounds().height/2.0);
    window->draw(titleText);
    
    
    //Press enter to play
    sf::Font enterFont;
    enterFont.loadFromFile(rPath + "sansation.ttf");
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
                else if(key_A) currLevel->balls.at(ballIndex).changeDirection((int) leftF);
                else if(key_W) {currLevel->balls.at(ballIndex).changeDirection((int) upF); key_W = false;}
                else if(key_S) {currLevel->balls.at(ballIndex).changeDirection((int) downF); key_S = false;}
                else if(key_E) ballIndex = currLevel->prevBall(); //Q and E keys are swapped here due to a bug with double counting taps.
                else if(key_Q) ballIndex = currLevel->nextBall(); //Q and E keys are swapped here due to a bug with double counting taps.
                else if(mouse_left) {
                    cout << "left mouse button.\n";
                    currLevel->checkForSQSelect(mouse_X, mouse_Y, "pop");
                    mouse_left = false;
                }
                else if(mouse_right) {
                    cout << "right mouse button.\n";
                    currLevel->checkForSQSelect(mouse_X, mouse_Y, "peek");
                    mouse_right = false;
                }
            }
        }
    }
    clear();
    delete currLevel;
    delete window;
    return 0;
}
