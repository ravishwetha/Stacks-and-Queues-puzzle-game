//Stacks and Queues
//Copyright © 2016 TeamSQ. All rights reserved.

//MainMenu.h

#ifndef MainMenu_h
#define MainMenu_h

#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <list>

#include "Globals.hpp"

class MainMenu
{
public:
    enum MenuResult{Nothing, Backup, Exit, Play, Help};
    
    struct MenuItem
    {
    public:
        sf::Rect<float> rect;
        MenuResult action;
    };
    
    MenuResult Show(sf::RenderWindow& window);
    
private:
    MenuResult GetMenuResponse(sf::RenderWindow& window);
    MenuResult HandleClick(int x, int y);
    std::list<MenuItem> menuItems;
};

#endif /* MainMenu_h */
