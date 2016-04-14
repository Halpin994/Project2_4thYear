#include "stdafx.h"
#include "Button.h"
#include "SFML/Graphics.hpp"
#include <SFML/OpenGL.hpp>

#include <iostream>

Button::~Button()
{
}

Button::Button(sf::Vector2f& pos, sf::String& string, int& size, sf::Font& font)
{
	buttonText.setPosition(pos);
	buttonText.setString(string);
	buttonText.setCharacterSize(size);
	buttonText.setFont(font);
	buttonText.setColor(sf::Color::White);
}

void Button::Update(sf::Vector2f& crosshairPos)
{
	if (buttonText.getGlobalBounds().contains(crosshairPos))
	{
		buttonText.setColor(sf::Color::Yellow);
	}
}

void Button::Draw(sf::RenderWindow& window)
{
	window.draw(buttonText);
}
