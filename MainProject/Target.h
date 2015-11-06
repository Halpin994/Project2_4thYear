#include <iostream>
using namespace std;

#ifndef TARGET
#define TARGET

class Target
{
public:
	Target();
	void Load();
	void SetUp();
	void Draw(sf::RenderWindow& window);
	sf::Vector2f Target::GetPosition();
	float Target::GetWidth();
	float Target::GetHeight();

private:
	sf::Texture targetImage;
	sf::Sprite targetSprite;

};

#endif 