//Stacks and Queues
//Copyright © 2016 TeamSQ. All rights reserved.

//LevelScreen.h

#ifndef LevelScreen_h
#define LevelScreen_h

#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <list>

#include "Globals.hpp"

class LevelScreen
{
public:
    enum LevelSelect{Nothing, Exit, lvl1, lvl2, lvl3};
    
    struct ScreenItem
    {
    public:
        sf::Rect<float> rect;
        LevelSelect action;
    };
    
    LevelSelect Show(sf::RenderWindow& window);
    
private:
    LevelSelect GetResponse(sf::RenderWindow& window);
    LevelSelect HandleClick(int x, int y);
    std::vector<ScreenItem> ScreenItems;
    
    void drawLocks(sf::RenderWindow& window);
};

#endif /* LevelScreen_h */
