//Stacks and Queues
//Copyright © 2016 TeamSQ. All rights reserved.

//LevelScreen.cpp

#include "LevelScreen.hpp"

LevelScreen::LevelSelect LevelScreen::Show(sf::RenderWindow& window)
{
    //Load menu image from file
    sf::Texture texture;
    if(!texture.loadFromFile(rPath + "LevelScreen.png")) cout << "Error loading LevelScreen.png";
    sf::Sprite sprite(texture);
    
    //Setup Clickable regions
    
    //Level buttons coordinates
    ScreenItem lvl1Button;
    lvl1Button.rect.top = RES_Y*(290/800.0);
    lvl1Button.rect.height = RES_Y*(134/800.0);
    lvl1Button.rect.left = RES_X*(400/1200.0);
    lvl1Button.rect.width = RES_X*(130/1200.0);
    lvl1Button.action = lvl1;
    
    ScreenItem lvl2Button;
    lvl2Button.rect.top = RES_Y*(290/800.0);
    lvl2Button.rect.height = RES_Y*(134/800.0);
    lvl2Button.rect.left = RES_X*(530/1200.0);
    lvl2Button.rect.width = RES_X*(130/1200.0);
    lvl2Button.action = lvl2;

    ScreenItem lvl3Button;
    lvl3Button.rect.top = RES_Y*(290/800.0);
    lvl3Button.rect.height = RES_Y*(134/800.0);
    lvl3Button.rect.left = RES_X*(660/1200.0);
    lvl3Button.rect.width = RES_X*(130/1200.0);
    lvl3Button.action = lvl3;
    
    //Exit menu item coordinates
    ScreenItem exitButton;
    exitButton.rect.top = RES_Y*(500/800.0);
    exitButton.rect.height = RES_Y*(134/800.0);
    exitButton.rect.left = RES_X*(400/1200.0);
    exitButton.rect.width = RES_X*(408/1200.0);
    exitButton.action = Exit;
    
    ScreenItems.push_back(lvl1Button);
    ScreenItems.push_back(lvl2Button);
    ScreenItems.push_back(lvl3Button);
    ScreenItems.push_back(exitButton);
    
    window.draw(sprite);
    drawLocks(window);
    window.display();
    
    return GetResponse(window);
}

LevelScreen::LevelSelect LevelScreen::HandleClick(int x, int y)
{
    std::vector<ScreenItem>::iterator it;
    
    for (it = ScreenItems.begin(); it != ScreenItems.end(); it++)
    {
        sf::Rect<float> menuItemRect = (*it).rect;
        if (menuItemRect.top < y && menuItemRect.left < x && (menuItemRect.top + menuItemRect.height) > y && (menuItemRect.left + menuItemRect.width) > x)
        {
            return (*it).action;
        }
    }
    return Nothing;
}

LevelScreen::LevelSelect  LevelScreen::GetResponse(sf::RenderWindow& window)
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

void LevelScreen::drawLocks(sf::RenderWindow& window) {
    int lvlButtonID = 0;
    float lockX = 0;
    float lockY = 0;
    for(int i=0; i<lockedLevels.size(); i++) {
        lvlButtonID = lockedLevels.at(i)-1;
        sf::Rect<float> buttonRect = ScreenItems.at(lvlButtonID).rect;
        lockX = buttonRect.left+(buttonRect.width/2.0);
        lockY = buttonRect.top+(buttonRect.height/2.0);
        
        sf::Texture lockTexture;
        if(!lockTexture.loadFromFile(rPath + "lock.png")) cout << "Error loading lock.png";
        //else cout << "Drew lock for level " << lvlButtonID + 1 << " at (" << lockX << ", " << lockY << ")" << "\n";
        sf::Sprite lockSprite(lockTexture);
        lockSprite.setPosition(lockX, lockY);
        lockSprite.setScale(0.2, 0.2);
        lockSprite.setColor(sf::Color::Yellow);
        window.draw(lockSprite);
    }
}