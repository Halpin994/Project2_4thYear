#include <iostream>
using namespace std;

#ifndef LEVEL
#define LEVEL

class Level
{
public:
	Level();
	void Load();
	void SetUp();
	void Draw(sf::RenderWindow& window);

private:
	sf::Texture rangeTexture;
	sf::Sprite rangeSprite;
};

#endif 