//Stacks and Queues
//Copyright © 2016 TeamSQ. All rights reserved.

//LevelScreen.cpp

#include "Menu.hpp"

Menu::MenuResult Menu::Show(sf::RenderWindow& window, int type) {
    
    menuItems.clear();
    this->type = type;
    
    if(type == 1) {
        //Load menu image from file
        sf::Texture texture;
        if(!texture.loadFromFile("MainMenu.png")) return Backup;
        sf::Sprite sprite(texture);
        
        float qmX = RES_X*0.92;
        float qmY = RES_Y*0.90;
        float qxSize = 600; //image is 600x600
        float qmScale = 0.1;
        //Question mark image
        sf::Texture lockTexture;
        if(!lockTexture.loadFromFile("questionmark.png")) cout << "Error loading questiomark.png";
        //else cout << "Drew question mark at (" << qmX << ", " << qmY << ")" << "\n";
        sf::Sprite lockSprite(lockTexture);
        lockSprite.setPosition(qmX, qmY);
        lockSprite.setScale(qmScale, qmScale);
        
        //Setup Clickable regions
        
        //Play menu item coordinates
        MenuItem playButton;
        playButton.rect.top = RES_Y*(290/800.0);
        playButton.rect.height = RES_Y*(134/800.0);
        playButton.rect.left = RES_X*(400/1200.0);
        playButton.rect.width = RES_X*(408/1200.0);
        playButton.action = Play;
        
        //Exit menu item coordinates
        MenuItem exitButton;
        exitButton.rect.top = RES_Y*(500/800.0);
        exitButton.rect.height = RES_Y*(134/800.0);
        exitButton.rect.left = RES_X*(400/1200.0);
        exitButton.rect.width = RES_X*(408/1200.0);
        exitButton.action = Exit;
        
        //Help page item coordinates
        MenuItem helpButton;
        helpButton.rect.top = qmY;
        helpButton.rect.height = qxSize*qmScale;
        helpButton.rect.left = qmX;
        helpButton.rect.width = qxSize*qmScale;
        helpButton.action = Help;
        
        menuItems.push_back(playButton);
        menuItems.push_back(exitButton);
        menuItems.push_back(helpButton);
        
        //Draw Sprites
        window.draw(sprite);
        window.draw(lockSprite);
        window.display();
        
        return GetResponse(window);
    }
    else if(type == 2) {
        //Level Select
        sf::Texture texture;
        if(!texture.loadFromFile("LevelScreen.png")) cout << "Error loading LevelScreen.png\n";
        //else cout << "Successfully loaded LevelScreen.png.\n";
        sf::Sprite sprite(texture);
        
        //Setup Clickable regions
        
        //Level buttons coordinates
        MenuItem lvl1Button;
        lvl1Button.rect.top = RES_Y*(290/800.0);
        lvl1Button.rect.height = RES_Y*(134/800.0);
        lvl1Button.rect.left = RES_X*(400/1200.0);
        lvl1Button.rect.width = RES_X*(130/1200.0);
        lvl1Button.action = lvl1;
        
        MenuItem lvl2Button;
        lvl2Button.rect.top = RES_Y*(290/800.0);
        lvl2Button.rect.height = RES_Y*(134/800.0);
        lvl2Button.rect.left = RES_X*(530/1200.0);
        lvl2Button.rect.width = RES_X*(130/1200.0);
        lvl2Button.action = lvl2;
        
        MenuItem lvl3Button;
        lvl3Button.rect.top = RES_Y*(290/800.0);
        lvl3Button.rect.height = RES_Y*(134/800.0);
        lvl3Button.rect.left = RES_X*(660/1200.0);
        lvl3Button.rect.width = RES_X*(130/1200.0);
        lvl3Button.action = lvl3;
        
        //Exit menu item coordinates
        MenuItem exitButton;
        exitButton.rect.top = RES_Y*(500/800.0);
        exitButton.rect.height = RES_Y*(134/800.0);
        exitButton.rect.left = RES_X*(400/1200.0);
        exitButton.rect.width = RES_X*(408/1200.0);
        exitButton.action = Exit;
        
        menuItems.push_back(lvl1Button);
        menuItems.push_back(lvl2Button);
        menuItems.push_back(lvl3Button);
        menuItems.push_back(exitButton);
        
        //cout << "Configured LevelScreen buttons.\n";
        
        window.draw(sprite);
        drawLocks(window);
        window.display();
        
        return GetResponse(window);
    }
    else if(type == 3) {
        //Help page
        sf::Texture texture;
        if(!texture.loadFromFile("help.png"));
        sf::Sprite sprite(texture);
        
        //Exit menu item coordinates
        MenuItem exitButton;
        exitButton.rect.top = 0;
        exitButton.rect.height = RES_Y;
        exitButton.rect.left = 0;
        exitButton.rect.width = RES_X;
        exitButton.action = Exitpage;
        
        menuItems.push_back(exitButton);
        float helpSizeX = 782;
        float helpSizeY = 750;
        sprite.setOrigin(helpSizeX/2.0, helpSizeY/2.0);
        sprite.setPosition(RES_X/2.0, RES_Y2);
        window.draw(sprite);
        window.display();
        
        return GetResponse(window);
    }
    else cout << "Error menu.Show precond: type can only be 1, 2 or 3 not satisfied";
}

Menu::MenuResult Menu::HandleClick(int x, int y)
{
    std::vector<MenuItem>::iterator it;
    
    for (it = menuItems.begin(); it != menuItems.end(); it++)
    {
        sf::Rect<float> menuItemRect = (*it).rect;
        if (menuItemRect.top < y && menuItemRect.left < x && (menuItemRect.top + menuItemRect.height) > y && (menuItemRect.left + menuItemRect.width) > x)
        {
            return (*it).action;
        }
    }
    return Nothing;
}

Menu::MenuResult Menu::GetResponse(sf::RenderWindow& window)
{
    sf::Event screenEvent;
    while (true)
    {
        while (window.pollEvent(screenEvent))
        {
            if (screenEvent.type == sf::Event::MouseButtonPressed)
            {
                return HandleClick(screenEvent.mouseButton.x, screenEvent.mouseButton.y);
            }
            
            if (screenEvent.type == sf::Event::Closed)
            {
                return Exit;
            }
        }
    }
}

void Menu::drawLocks(sf::RenderWindow& window) {
    int lvlButtonID = 0;
    float lockX = 0;
    float lockY = 0;
    for(int i=0; i<lockedLevels.size(); i++) {
        if(lockedLevels.at(i) != 0) lvlButtonID = lockedLevels.at(i)-1;
        else continue;
        sf::Rect<float> buttonRect = menuItems.at(lvlButtonID).rect;
        lockX = buttonRect.left+(buttonRect.width/2.0);
        lockY = buttonRect.top+(buttonRect.height/2.0);
        
        sf::Texture lockTexture;
        if(!lockTexture.loadFromFile("lock.png")) cout << "Error loading lock.png";
        //else cout << "Drew lock for level " << lvlButtonID + 1 << " at (" << lockX << ", " << lockY << ")" << "\n";
        sf::Sprite lockSprite(lockTexture);
        lockSprite.setPosition(lockX, lockY);
        lockSprite.setScale(0.2, 0.2);
        window.draw(lockSprite);
    }
}