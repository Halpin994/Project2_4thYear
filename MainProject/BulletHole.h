#include <iostream>
#include <list>
using namespace std;

#ifndef BULLETHOLE
#define BULLETHOLE

class BulletHole
{
public:
	BulletHole();
	~BulletHole()
	{
		cout << "Bullets deleted" << endl;
	}
	BulletHole(sf::Vector2f, static int bulletType, sf::Texture* bulletImage);
	void Draw(sf::RenderWindow& window);
	sf::Vector2f BulletHole::GetBulletPosition();
	
private:
	sf::Sprite bulletHoleSprite;
	int targetCollided;
};
#endif 