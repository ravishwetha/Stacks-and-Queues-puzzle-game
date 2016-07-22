//Stacks and Queues
//Copyright © 2016 TeamSQ. All rights reserved.

//main.cpp

//#include "SplashScreen.h"
#include "LevelScreen.hpp"
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

std::vector<int> lockedLevels = {2, 3};
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
    //tQueue lvl1queue1 = tQueue(RES_X*(0.50), RES_Y*(0.40), radius*6, radius*2);
    
    //cout << "Level 1 objects initialised.\n";
    
    //store objects in level
    level1->balls.push_back(lvl1ball1);
    level1->balls.push_back(lvl1ball3);
    level1->balls.push_back(lvl1ball4);
    //cout << "From main.cpp (just created) Level 1 has " << level1->balls.size() << " balls.\n";
    
    level1->stacks.push_back(lvl1stack1);
    //level1->queues.push_back(lvl1queue1);
    
    //cout << "Level 1 vectors initialised.\n";
    
    ballIndex = 0;
    currLevel = level1;
    
    cout << "Level 1 initialised.\n";
}

void initialiseLevel2() {
    std::vector<string> winOrder = {"m", "a", "g", "e"};
    level2 = new Level(1, winOrder); //num is (level number - 1)
    
    //get level info
    float x = level2->getInTubePositionX();
    float y = level2->getInTubePositionY();
    float vx1 = level2->getBallVX();
    float vy1 = vx1*3;
    float radius = level2->getBallRadius();
    
    //create level objects accordingly
    Ball lvl2ballm = Ball(0, x - (radius*7), y, vx1, vy1, radius, sf::Color::Red, "m");
    Ball lvl2balla = Ball(1, x - (radius*5), y, vx1, vy1, radius, sf::Color::Red, "a");
    Ball lvl2ballg = Ball(2, x - (radius*3), y, vx1, vy1, radius, sf::Color::Red, "g");
    Ball lvl2balle = Ball(3, x - (radius), y, vx1, vy1, radius, sf::Color::Red, "e");
    
    tStack lvl2stack1 = tStack(RES_X*(0.50), RES_Y*(0.60), radius*2, radius*6);
    tQueue lvl2queue1 = tQueue(RES_X*(0.50), RES_Y*(0.40), radius*6, radius*2);
    
    //cout << "Level 2 objects initialised.\n";
    
    //store objects in level
    level2->balls.push_back(lvl2ballm);
    level2->balls.push_back(lvl2balla);
    level2->balls.push_back(lvl2ballg);
    level2->balls.push_back(lvl2balle);
    
    level2->stacks.push_back(lvl2stack1);
    level2->queues.push_back(lvl2queue1);
    
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
    Ball lvl3balls = Ball(0, x - (radius*9), y, vx1, vy1, radius, sf::Color::Red, "s");
    Ball lvl3ballt = Ball(1, x - (radius*7), y, vx1, vy1, radius, sf::Color::Red, "t");
    Ball lvl3balla = Ball(2, x - (radius*5), y, vx1, vy1, radius, sf::Color::Red, "a");
    Ball lvl3ballc = Ball(3, x - (radius*3), y, vx1, vy1, radius, sf::Color::Red, "c");
    Ball lvl3ballk = Ball(4, x - (radius), y, vx1, vy1, radius, sf::Color::Red, "k");
    
    tStack lvl3stack1 = tStack(RES_X*(0.50), RES_Y*(0.60), radius*2, radius*6);
    tQueue lvl3queue1 = tQueue(RES_X*(0.50), RES_Y*(0.40), radius*6, radius*2);
    
    //cout << "Level 3 objects initialised.\n";
    
    //store objects in level
    level3->balls.push_back(lvl3balls);
    level3->balls.push_back(lvl3ballt);
    level3->balls.push_back(lvl3balla);
    level3->balls.push_back(lvl3ballc);
    level3->balls.push_back(lvl3ballk);
    
    level3->stacks.push_back(lvl3stack1);
    level3->queues.push_back(lvl3queue1);
    
    //cout << "Level 3 vectors initialised.\n";
    
    ballIndex = 0;
    
    cout << "Level 3 initialised.\n";
}

void initialiseGame() {
    initialiseLevel1();
    //cout << level1->winOrder.at(0);
    initialiseLevel2();
    //cout << level2->winOrder.at(0);
    initialiseLevel3();
    //cout << level3->winOrder.at(0);
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

void unlockNextLevel(int num) {
    switch(num) {
        case 1: level2->toggleUnlocked(); cout << "Level 2 unlocked.\n"; break;
        case 2: level3->toggleUnlocked(); cout << "Level 3 unlocked.\n"; break;
        default: return;
    }
    lockedLevels.erase(lockedLevels.begin());
}

void updateGame() {
    int status;
    cout << "Update current level: " << currLevel->winOrder.at(0) << "\n";
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
    LevelScreen levelscreen;
    MainMenu mainmenu;
    initialiseGame();
    
    sf::Event event;
    while (window->isOpen()) {
        if(reinitialise) {
            clear();
            initialiseGame();
            reinitialise = false;
        }
        
        //MAIN MENU AND LEVEL SELECT
        if(!gameRunning) {
            //pressed escape
            bool play = false; //exited choose level or the game
            clear();
            if(!window->isOpen()) break;
            else {
                window->clear();
                switch(mainmenu.Show(*window)) {
                    case MainMenu::MenuResult::Backup: backupMainMenu(); break;
                    case MainMenu::MenuResult::Exit: exitGame(); break;
                    case MainMenu::MenuResult::Play: {
                        if(!window->isOpen()) break;
                        window->clear();
                        switch(levelscreen.Show(*window)) {
                            case LevelScreen::LevelSelect::lvl1: cout << "selected lvl1.\n"; currLevel = level1; play = true; break;
                            case LevelScreen::LevelSelect::lvl2: cout << "selected lvl2.\n"; if(level2->unlocked) { currLevel = level2; play = true; } break;
                            case LevelScreen::LevelSelect::lvl3: cout << "selected lvl3.\n"; if(level3->unlocked) { currLevel = level3; play = true; } break;
                            case LevelScreen::LevelSelect::Exit: exitGame(); break;
                            case LevelScreen::LevelSelect::Nothing: ; break;
                        }
                        if(play) {
                            //cout << "Level 1 isActive: " << level1->isActive << ".\n";
                            //cout << "Level 2 isActive: " << level2->isActive << ".\n";
                            //cout << "Level 3 isActive: " << level3->isActive << ".\n";
                            cout << "Loading Level " << currLevel->num+1 << "...\n";
                            gameRunning = true;
                            gameNotPaused = true; break;
                        }
                    }
                    case MainMenu::MenuResult::Nothing: ;
                    default: ;
                }
            }
        }
        
        //GAME RUNNING BUT PAUSED
        else if(gameRunning && !gameNotPaused) {
            //cout << "Game is paused.\n";
            
            while(window->pollEvent(event)) {
                processEvent(event);
                if(key_escape) {
                    //cout << "Escape key pressed.\n";
                    gameRunning = false;
                    gameNotPaused = true;
                    reinitialise = true;
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
                    //cout << "Escape key pressed.\n";
                    gameRunning = false;
                    gameNotPaused = true;
                    reinitialise = true;
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
    delete currLevel;
    delete window;
    return 0;
}
