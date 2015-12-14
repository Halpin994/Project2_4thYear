#include <iostream>
using namespace std;

#ifndef TARGET
#define TARGET

class Target
{
public:
	Target();
	void SetUp(sf::Vector2f, sf::Texture* targetImage, float);
	void Draw(sf::RenderWindow& window);
	sf::Vector2f Target::GetPosition();
	float Target::GetWidth();
	float Target::GetHeight();
	float Target::GetHealth();
	void Target::SetHealth();
	void Target::SetPosition(sf::Vector2f);

private:
	sf::Texture targetTexture;
	sf::Sprite targetSprite;

	float targetHealth;


};

#endif 