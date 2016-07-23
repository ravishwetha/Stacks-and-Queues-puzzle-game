//Stacks and Queues
//Copyright © 2016 TeamSQ. All rights reserved.

//Menu.hpp

#ifndef Menu_h
#define Menu_h

#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <list>

#include "Globals.hpp"

class Menu
{
public:
    enum MenuResult{Nothing, Backup, Exit, Play, Help, lvl1, lvl2, lvl3, Exitpage};
    
    struct MenuItem
    {
    public:
        sf::Rect<float> rect;
        MenuResult action;
    };
    
    MenuResult Show(sf::RenderWindow& window, int type);
    
private:
    //types- 1: main menu, 2: level select, 3: help page, precond: type can only be 1, 2, or 3
    int type;
    std::vector<MenuItem> menuItems;
    
    MenuResult GetResponse(sf::RenderWindow& window);
    MenuResult HandleClick(int x, int y);
    void drawLocks(sf::RenderWindow& window);
};

#endif /* Menu_h */
