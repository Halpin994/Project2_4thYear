#include <iostream>
#include <list>
using namespace std;

#ifndef BULLETHOLE
#define BULLETHOLE

class BulletHole
{
public:
	BulletHole();
	void SetUp(int textureType, sf::Vector2f, sf::Texture* bulletMetalImage,sf::Texture* bulletWoodImage);
	void Draw(sf::RenderWindow& window);

private:
	sf::Sprite bulletHoleSprite;

};
#endif 