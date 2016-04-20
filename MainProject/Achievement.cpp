#include "stdafx.h"
#include "Achievement.h"


Achievement::Achievement()
{
	mySprite.setPosition(sf::Vector2f(0, 0));
	unlocked = false;
}

Achievement::~Achievement()
{
}

void Achievement::SetPosition(sf::Vector2f pos)
{
	mySprite.setPosition(pos);
}

void Achievement::Draw(sf::RenderWindow& window)
{
	window.draw(mySprite);
}