#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>

class Achievement
{
public:

	void SetPosition(sf::Vector2f pos);
	void Draw(sf::RenderWindow& window);
	bool unlocked;

protected:

	Achievement();
	~Achievement();

	sf::Sprite mySprite;
	sf::Texture myTexture;
	sf::Vector2f myPosition;
};


class CrackShot : public Achievement
{
public:
	CrackShot()
	{
		myTexture.loadFromFile("Assets/Images/Game/crackshot.png");
		mySprite.setTexture(myTexture);
	}
	~CrackShot();
};

class CrapShot : public Achievement
{
public:
	CrapShot()
	{
		myTexture.loadFromFile("Assets/Images/Game/crapshot.png");
		mySprite.setTexture(myTexture);
	}
	~CrapShot();
};
