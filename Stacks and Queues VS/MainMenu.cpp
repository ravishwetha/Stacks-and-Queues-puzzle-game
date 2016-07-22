//Stacks and Queues
//Copyright © 2016 TeamSQ. All rights reserved.

//MainMenu.cpp

#include "stdafx.h"
#include "MainMenu.h"

MainMenu::MenuResult MainMenu::Show(sf::RenderWindow& window)
{
    //Load menu image from file
    sf::Texture texture;
    if(!texture.loadFromFile("MainMenu.png")) return Backup;
    sf::Sprite sprite(texture);
    
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
    
    menuItems.push_back(playButton);
    menuItems.push_back(exitButton);
    
    window.draw(sprite);
    window.display();
    
    return GetMenuResponse(window);
}

MainMenu::MenuResult MainMenu::HandleClick(int x, int y)
{
    std::list<MenuItem>::iterator it;
    
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

MainMenu::MenuResult  MainMenu::GetMenuResponse(sf::RenderWindow& window)
{
    sf::Event menuEvent;
    while (true)
    {
        while (window.pollEvent(menuEvent))
        {
            if (menuEvent.type == sf::Event::MouseButtonPressed)
            {
                return HandleClick(menuEvent.mouseButton.x, menuEvent.mouseButton.y);
            }
            
            if (menuEvent.type == sf::Event::Closed)
            {
                return Exit;
            }
        }
    }
}
