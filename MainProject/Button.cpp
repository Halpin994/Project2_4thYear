#include "stdafx.h"
#include "Button.h"
#include "SoundManager.h"
#include "Menu.h"

#include "SFML/Graphics.hpp"
#include <SFML/OpenGL.hpp>

#include <iostream>

Button::~Button()
{
}

Button::Button(sf::Vector2f pos, sf::String string, int size, sf::Font& font, void (Menu::*MenuMemFunc)())
{
	buttonText.setPosition(pos);
	buttonText.setString(string);
	buttonText.setCharacterSize(size);
	buttonText.setFont(font);
	buttonText.setColor(sf::Color::White);
	highlighted = false;
	clicked = false;
	btn_Func = MenuMemFunc;
}

void Button::Update(sf::Vector2f crosshairPos, Menu* menu)
{
	if (buttonText.getGlobalBounds().contains(crosshairPos))
	{
		if (highlighted == false)
		{
			clicked = false;
			highlighted = true;
			buttonText.setColor(sf::Color(255,255,0,255));
			SoundManager::GetInstance()->PlayClick();
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && clicked == false)
		{
			menu->SetSecondButtonPressed(buttonText.getString());
			(menu->*btn_Func)();
			menu->SetFirstButtonPressed(buttonText.getString());

			SoundManager::GetInstance()->PlayPistolGunShot();
			clicked = true;
		}
	}
	else
	{
		buttonText.setColor(sf::Color::White);
		highlighted = false;
	}
	
}

void Button::Draw(sf::RenderWindow& window)
{
	window.draw(buttonText);
}

sf::FloatRect Button::GetBounds()
{
	return buttonText.getGlobalBounds();
}
sf::Vector2f Button::GetPosition()
{
	return buttonText.getPosition();
}

