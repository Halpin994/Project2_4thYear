#include <iostream>
using namespace std;

#ifndef TARGET
#define TARGET

class Target
{
public:
	Target();
	void SetUp(sf::Vector2f, sf::Texture* targetImage);
	void Draw(sf::RenderWindow& window);
	sf::Vector2f Target::GetPosition();
	float Target::GetWidth();
	float Target::GetHeight();

private:
	sf::Texture targetTexture;
	sf::Sprite targetSprite;

};

#endif 