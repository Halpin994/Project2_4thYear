#include <iostream>
using namespace std;

#ifndef PLAYER
#define PLAYER

class Player
{
public:
	Player();
	~Player();
	void Init(sf::RenderWindow& window);
	void Load();
	void SetUp();
	void Draw(sf::RenderWindow& window);
	void Shoot(sf::RenderWindow& window);
	void Recoil(sf::RenderWindow& window, float);
	void Update(sf::RenderWindow& window, float);
	sf::Vector2f Normalize(sf::Vector2i);
	float getVectorLength(sf::Vector2i vec);

private:
	sf::Texture crosshairImage;
	sf::Sprite crosshairSprite;
	sf::Vector2f recoilDirection;
	bool mousePressed;
	bool recoilActive;
	float recoilTime;
	float recoilSpeed;
	sf::Vector2f offset;
	float random;

};

#endif 