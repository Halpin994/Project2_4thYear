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
	void SetUp(sf::Vector2f, sf::Texture* targetImage, sf::Texture*, float, int);
	void Draw(sf::RenderWindow& window);
	sf::Vector2f Target::GetPosition();
	float Target::GetWidth();
	float Target::GetHeight();
	float Target::GetHealth();
	void Target::SetHealth();
	void Target::SetPosition(sf::Vector2f);
	void Target::AddBullet(sf::Vector2f, static int bulletType);
	int Target::GetLayer();
	float Target::GetTimeToLive();

	void Update(float);


private:
	sf::Texture targetTexture;
	sf::Sprite targetSprite;

	float targetHealth;
	int targetLayer; //layers 1-3

	float timeToLive;

	list<BulletHole*>bullets;

	sf::Texture* bulletWoodTexture;
};

#endif 