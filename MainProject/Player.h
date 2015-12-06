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
	void Player::CreateGunClip();

private:
	sf::Texture crosshairImage;
	sf::Sprite crosshairSprite;
	//sf::Texture clipBulletImage;
	//sf::Sprite clipBulletSprite;

	sf::Vector2f recoilDirection;
	sf::Vector2f offset;
	sf::Vector2f myOffset;

	bool mousePressed;
	bool recoilActive;
	bool recoilTimerActive;

	bool recoilCalculated;
	bool recoilUp;

	float random;
	float recoilTime;
	float recoilSpeed;
	float recoilDistance;

	float recoilCoolDownTime;
	float recoilCoolDown;
	float yRecoil;
	float yRecoilStrength;
	float yRecoilStrengthTemp;
	float randomXSway;
	float recoilMultiplier;

	int recoilType;
	int pistolClipSize;
	int pistolClip;

};

#endif 