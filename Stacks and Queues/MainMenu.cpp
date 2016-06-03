#include <stdafx.h>

#include "MainMenu.h"

MainMenu::MenuResult MainMenu::Show(sf::RenderWindow& window)
{
	//Load menu image from file
	sf::Texture texture;
	texture.loadFromFile("MainMenu.png");
	sf::Sprite sprite(texture);

	//Setup Clickable regions

	//Play menu item coordinates
	MenuItem playButton;
	playButton.rect.top = 388;
	playButton.rect.height = 164;
	playButton.rect.left = 280;
	playButton.rect.width = 424;
	playButton.action = Play;

	//Exit menu item coordinates
	MenuItem exitButton;
	exitButton.rect.top = 490;
	exitButton.rect.height = 164;
	exitButton.rect.left = 280;
	exitButton.rect.width = 424;
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
		sf::Rect<int> menuItemRect = (*it).rect;
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