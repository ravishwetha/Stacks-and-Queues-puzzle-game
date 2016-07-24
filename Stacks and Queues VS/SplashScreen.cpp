//Stacks and Queues
//Copyright © 2016 TeamSQ. All rights reserved.

//SplashScreen.cpp

//#include <stdafx.h> //uncomment if using visual studio
#include "Globals.hpp"
#include "SplashScreen.h"

void SplashScreen::Show(sf::RenderWindow& renderWindow)
{
	sf::Texture texture;
	if (texture.loadFromFile("SplashScreen.cpp") != true)
	{
		return;
	}

	sf::Sprite sprite(texture);

	renderWindow.draw(sprite);
	renderWindow.display();

	sf::Event event;
	while (true)
	{
		while (renderWindow.pollEvent(event))
		{
			if (event.type == sf::Event::EventType::KeyPressed || event.type == sf::Event::EventType::MouseButtonPressed || event.type == sf::Event::EventType::Closed)
			{
				return;
			}
		}
	}
	
}
