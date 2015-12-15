#include <iostream>
using namespace std;

#ifndef TARGET
#define TARGET

#include "BulletHole.h"
#include <list>

class Target
{
public:
	Target();
	~Target()
	{
		cout << "Target Deleted" << endl;
		for (BulletHole* b : bullets)
		{
			delete b;
		}
	}
	void SetUp(sf::Vector2f, sf::Texture* targetImage, sf::Texture*, float);
	void Draw(sf::RenderWindow& window);
	sf::Vector2f Target::GetPosition();
	float Target::GetWidth();
	float Target::GetHeight();
	float Target::GetHealth();
	void Target::SetHealth();
	void Target::SetPosition(sf::Vector2f);
	void AddBullet(sf::Vector2f);

private:
	sf::Texture targetTexture;
	sf::Sprite targetSprite;

	float targetHealth;

	list<BulletHole*>bullets;

	sf::Texture* bulletWoodTexture;
};

#endif 