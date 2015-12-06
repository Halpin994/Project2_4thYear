#include <iostream>
using namespace std;

#include "SFML\Audio.hpp"

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
	sf::Vector2f Normalize(sf::Vector2f);
	float getVectorLength(sf::Vector2i vec);
	float Player::getRecoilDistance();
	sf::Vector2f Player::getRandomSway();

private:
	sf::Texture crosshairImage;
	sf::Sprite crosshairSprite;
	sf::Vector2f recoilDirection;
	bool mousePressed;
	bool recoilActive;
	bool recoilTimerActive;
	float recoilTime;
	float recoilSpeed;
	sf::Vector2f offset;
	float random;
	int recoilType;
	float recoilDistance;
	bool recoilCalculated;
	bool recoilUp;
	sf::Vector2f myOffset;

	sf::Sound sound;
	sf::SoundBuffer buffer;

	float recoilCoolDownTime;
	float recoilCoolDown;
	float yRecoil;
	float yRecoilStrength;
	float yRecoilStrengthTemp;
	float randomXSway;

};

#endif 