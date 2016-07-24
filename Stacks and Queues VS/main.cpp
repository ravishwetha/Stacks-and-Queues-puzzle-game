//Stacks and Queues
//Copyright © 2016 TeamSQ. All rights reserved.

//main.cpp

//#include "SplashScreen.h"
#include <SFML/Audio.hpp>
#include "Menu.hpp"
#include "Level.hpp"

///Globals
float RES_X = 1200;
float RES_Y = 800;
float RES_Y2 = RES_Y/2.0;
sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(RES_X, RES_Y), "Stacks and Queues");

std::vector<float> pathCoords;
float leftF = 1.0;
float upF = 2.0;
float downF = 3.0;

std::vector<int> lockedLevels = {2, 3};
std::vector<float> inTubePositionX = { RES_X, RES_X , RES_X };
std::vector<float> inTubePositionY = { RES_Y2, RES_Y2, RES_Y2 };
std::vector<float> ballsPeriod = { 5.0, 2.0, 2.0 };
std::vector<float> ballsVX = { 1.0, 1.0, 1.0 };
std::vector<float> ballsRadii = { 10, 10, 10 };

//Window
sf::Color backgroundColor = sf::Color::White;

//Game
int ballIndex = 0;
Level* currLevel;
Level* level1;
Level* level2;
Level* level3;

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
            //cout << "from main.cpp: x = " << mouse_X << " y = " << mouse_Y << ".\n";
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
    Ball ball0 = Ball(0, x - (radius*5), y, vx1, vy1, radius, sf::Color::Red, "1");
    Ball ball1 = Ball(1, x - (radius*3), y, vx1, vy1, radius, sf::Color::Red, "3");
    Ball ball2 = Ball(2, x - (radius), y, vx1, vy1, radius, sf::Color::Red, "4");
    
    tStack stack1 = tStack(RES_X*(0.50), RES_Y*(0.60), radius*2, radius*6);
    
    //cout << "Level 1 objects initialised.\n";
    
    //store objects in level
    level1->balls.push_back(ball0);
    level1->balls.push_back(ball1);
    level1->balls.push_back(ball2);
    //cout << "From main.cpp (just created) Level 1 has " << level1->balls.size() << " balls.\n";
    
    level1->stacks.push_back(stack1);

    //cout << "Level 1 vectors initialised.\n";
    
    ballIndex = 0;
    
    cout << "Level 1 initialised.\n";
}

void initialiseLevel2() {
    std::vector<string> winOrder = {"g", "a", "m", "e"};
    level2 = new Level(1, winOrder); //num is (level number - 1)
    
    //get level info
    float x = level2->getInTubePositionX();
    float y = level2->getInTubePositionY();
    float vx1 = level2->getBallVX();
    float vy1 = vx1*3;
    float radius = level2->getBallRadius();
    
    //create level objects accordingly
    Ball ball0 = Ball(0, x - (radius*7), y, vx1, vy1, radius, sf::Color::Red, "m");
    Ball ball1 = Ball(1, x - (radius*5), y, vx1, vy1, radius, sf::Color::Red, "a");
    Ball ball2 = Ball(2, x - (radius*3), y, vx1, vy1, radius, sf::Color::Red, "g");
    Ball ball3 = Ball(3, x - (radius), y, vx1, vy1, radius, sf::Color::Red, "e");
    
    tStack stack1 = tStack(RES_X*(0.50), RES_Y*(0.60), radius*2, radius*6);
    tQueue queue1 = tQueue(RES_X*(0.50), RES_Y*(0.40), radius*6, radius*2);
    
    //cout << "Level 2 objects initialised.\n";
    
    //store objects in level
    level2->balls.push_back(ball0);
    level2->balls.push_back(ball1);
    level2->balls.push_back(ball2);
    level2->balls.push_back(ball3);
    
    level2->stacks.push_back(stack1);
    level2->queues.push_back(queue1);
    
    //cout << "Level 2 vectors initialised.\n";
    
    ballIndex = 0;
    
    cout << "Level 2 initialised.\n";
}

void initialiseLevel3() {
    std::vector<string> winOrder = {"s", "t", "a", "c", "k"};
    level3 = new Level(2, winOrder); //num is (level number - 1)
    
    //get level info
    float x = level3->getInTubePositionX();
    float y = level3->getInTubePositionY();
    float vx1 = level3->getBallVX();
    float vy1 = vx1*3;
    float radius = level3->getBallRadius();
    
    //create level objects accordingly
    Ball ball0 = Ball(0, x - (radius*9), y, vx1, vy1, radius, sf::Color::Red, "s");
    Ball ball1 = Ball(1, x - (radius*7), y, vx1, vy1, radius, sf::Color::Red, "a");
    Ball ball2 = Ball(2, x - (radius*5), y, vx1, vy1, radius, sf::Color::Red, "k");
    Ball ball3 = Ball(3, x - (radius*3), y, vx1, vy1, radius, sf::Color::Red, "t");
    Ball ball4 = Ball(4, x - (radius), y, vx1, vy1, radius, sf::Color::Red, "c");
    
    //tStack stack1 = tStack(RES_X*(0.50), RES_Y*(0.60), radius*2, radius*6);
    tQueue queue1 = tQueue(RES_X*(0.50), RES_Y*(0.40), radius*6, radius*2);
    tQueue queue2 = tQueue(RES_X*(0.50), RES_Y*(0.60), radius*6, radius*2);
    
    //cout << "Level 3 objects initialised.\n";
    
    //store objects in level
    level3->balls.push_back(ball0);
    level3->balls.push_back(ball1);
    level3->balls.push_back(ball2);
    level3->balls.push_back(ball3);
    level3->balls.push_back(ball4);
    
    //level3->stacks.push_back(stack1);
    level3->queues.push_back(queue1);
    level3->queues.push_back(queue2);
    
    //cout << "Level 3 vectors initialised.\n";
    
    ballIndex = 0;
    
    cout << "Level 3 initialised.\n";
}

void initialiseGame() {
    initialiseLevel1();
    initialiseLevel2();
    initialiseLevel3();
}

void backupMainMenu() {
    window->clear();
    
    sf::Font titleFont;
    titleFont.loadFromFile("sansation.ttf");
    sf::Text titleText("Stacks and Queues", titleFont);
    titleText.setCharacterSize(RES_X/25.0);
    titleText.setStyle(sf::Text::Bold);
    titleText.setColor(sf::Color::White);
    titleText.setPosition(RES_X/2 - titleText.getLocalBounds().width/2.0, (RES_Y*(0.45)) - titleText.getLocalBounds().height/2.0);
    window->draw(titleText);
    
    
    //Press enter to play
    sf::Font enterFont;
    enterFont.loadFromFile("sansation.ttf");
    sf::Text enterText("Click Title to play", enterFont);
    enterText.setCharacterSize(RES_X/50.0);
    enterText.setStyle(sf::Text::Bold);
    enterText.setColor(sf::Color::White);
    enterText.setPosition(RES_X/2 - enterText.getLocalBounds().width/2.0, (RES_Y*(0.55)) - enterText.getLocalBounds().height/2.0);
    window->draw(enterText);
    
    window->display();
}

void printINTVector(std::vector<int> vec) {
    cout << "{";
    for(int i=0; i<vec.size(); i++) {
        if(i != vec.size()-1) cout << vec.at(i) << ", ";
        else cout << vec.at(i);
    }
    cout << "}\n";
}

bool isLocked(int num) {
    for(int i=0; i<lockedLevels.size(); i++) {
        if(lockedLevels.at(i) == num) return true; //num is locked
    }
    return false; //num is unlocked
}

void unlockNextLevel(int num) {
    //cout << "Current Level is " << num << " Next Level is " << num + 1 << " at index " << num - 1 <<".\n";
    if(num - 1 < lockedLevels.size()) {
        lockedLevels.at(num - 1) = 0;
        cout << "Level " << num + 1 << " unlocked.\n";
    }
    else cout << "Unlocked all levels! Thank you for playing Stacks and Queues version 1.0.\n";
    
    //cout << "Locked levels: ";
    //printINTVector(lockedLevels);
}

void updateGame() {
    int status;
    status = currLevel->updateLevel();
    switch(status) {
        case 1: cout << "Won Level " << currLevel->num+1 << ", unlocking next level... \n"; unlockNextLevel(currLevel->num+1); break; //level won
        case -1: cout << "Lost level " << currLevel->num+1 << ", did not unlock any level\n"; break;
        default: ; //do nothing
    }
}

void drawGameFrame() {
    currLevel->drawLevel();
}

void clear() {
    currLevel->clearLevel();
}

void exitGame() {
    clear();
    window->close();
}

int main() {
    bool reinitialise = false;
    bool gameRunning = false;
    bool gameNotPaused = true;
    
    sf::Clock clock;
    float frameTime = 1/60.0f;
    float dTime = 0;
    
    //SplashScreen splashscreen;
    Menu menu;
    //LevelScreen levelscreen;
    //MainMenu mainmenu;
    initialiseGame();
    currLevel = level1;
    //printINTVector(lockedLevels);
    //cout << "Iniitialised all levels " << currLevel->num+1 << " no. of balls: " << currLevel->balls.size() << " " << level1->balls.size() << "\n";
    
    sf::Event event;
    while (window->isOpen()) {
        if(reinitialise) {
            clear();
            initialiseGame();
            cout << "Locked levels: ";
            printINTVector(lockedLevels);
            reinitialise = false;
        }
        
        //MAIN MENU AND LEVEL SELECT
        if(!gameRunning) {
            //pressed escape
            bool play = false; //exited choose level or the game
            if(!window->isOpen()) break;
            else {
                window->clear();
                switch(menu.Show(*window, 1)) {
                    case Menu::MenuResult::Backup: backupMainMenu(); break;
                    case Menu::MenuResult::Exit: exitGame(); break;
                    case Menu::MenuResult::Play: {
                        if(!window->isOpen()) break;
                        cout << "selected Play.\n";
                        window->clear();
                        switch(menu.Show(*window, 2)) {
                            case Menu::MenuResult::lvl1: cout << "selected lvl1.\n"; currLevel = level1; play = true; break;
                            case Menu::MenuResult::lvl2: cout << "selected lvl2.\n"; if(!isLocked(2)) { currLevel = level2; play = true; } else cout << "Sorry lvl2 is locked.\n"; break;
                            case Menu::MenuResult::lvl3: cout << "selected lvl3.\n"; if(!isLocked(3)) { currLevel = level3; play = true; } else cout << "Sorry lvl3 is locked.\n"; break;
                            case Menu::MenuResult::Exit: exitGame(); break;
                            case Menu::MenuResult::Nothing: ; break;
                            default: ;
                        }
                        if(play) {
                            cout << "Loading Level " << currLevel->num+1 << "...\n";
                            gameRunning = true;
                            gameNotPaused = true; break;
                        }
                        break;
                    }
                    case Menu::MenuResult::Help: {
                        cout << "Clicked on help.\n";
                        window->clear(sf::Color::White);
                        switch(menu.Show(*window, 3)) {
                            case Menu::MenuResult::Exitpage: cout << "Back to main menu.\n"; break;
                            default: ;
                        }
                        break;
                    }
                    case Menu::MenuResult::Nothing: ;
                    default: ;
                }
            }
        }
        
        //GAME RUNNING BUT PAUSED
        else if(gameRunning && !gameNotPaused) {
            cout << "Game is paused.\n";
            
            while(window->pollEvent(event)) {
                processEvent(event);
                if(key_escape) {
                    cout << "Level exited.\n";
                    gameRunning = false;
                    gameNotPaused = true;
                    reinitialise = true;
                }
                else if(key_return) {
                    cout << "Game resumed.\n";
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
                //cout << "Playing Level " << currLevel->num+1 << "\n";
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
                    cout << "Level exited.\n";
                    cout << "\n";
                    gameRunning = false;
                    gameNotPaused = true;
                    reinitialise = true;
                    key_escape = false;
                }
                else if(key_P) {
                    cout << "Game is paused.\n";
                    gameRunning = true;
                    gameNotPaused = false;
                }
                else if(key_A) currLevel->balls.at(ballIndex).changeDirection((int) leftF);
                else if(key_W) {currLevel->balls.at(ballIndex).changeDirection((int) upF); key_W = false;}
                else if(key_S) {currLevel->balls.at(ballIndex).changeDirection((int) downF); key_S = false;}
                else if(key_Q) {ballIndex = currLevel->prevBall(); key_Q = false;}//cout << "Q\n";}
                else if(key_E) {ballIndex = currLevel->nextBall(); key_E = false;}//cout << "E\n";}
                else if(mouse_left) {
                    //cout << "left mouse button.\n";
                    currLevel->checkForSQSelect(mouse_X, mouse_Y, "pop");
                    mouse_left = false;
                }
                else if(mouse_right) {
                    //cout << "right mouse button.\n";
                    currLevel->checkForSQSelect(mouse_X, mouse_Y, "peek");
                    mouse_right = false;
                }
            }
        }
    }
    delete currLevel;
    delete window;
    return 0;
}
