#include "stdafx.h"
#include "SFML/Graphics.hpp"
#include <SFML/OpenGL.hpp>

#include <iostream>
#include "Target.h"

Target::Target()
{
	Load();
	SetUp();
}

void Target::Load()
{
	targetImage.loadFromFile("target.png");
}

void Target::SetUp()
{
	targetSprite.setTexture(targetImage, true);
	targetSprite.setPosition(600 - targetSprite.getGlobalBounds().width / 2, 180);
}

void Target::Draw(sf::RenderWindow& window)
{
	window.draw(targetSprite);
}

sf::Vector2f Target::GetPosition()
{
	return targetSprite.getPosition();
}

float Target::GetWidth()
{
	return targetSprite.getGlobalBounds().width;
}

float Target::GetHeight()
{
	return targetSprite.getGlobalBounds().height;
}