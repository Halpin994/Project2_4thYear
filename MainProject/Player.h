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
	void CrosshairRecoil(sf::RenderWindow& window, float);
	sf::Vector2f Player::PistolBulletRecoil();
	void Update(sf::RenderWindow& window, float);
	sf::Vector2f Normalize(sf::Vector2f);
	float getVectorLength(sf::Vector2i vec);
	float Player::getcrhRecoilDistance();
	sf::Vector2f Player::getRandomSway();
	void Player::CreateGunClip();

private:
	sf::Texture crosshairImage;
	sf::Sprite crosshairSprite;
	sf::Texture clipBulletImage;
	sf::Sprite clipBulletSprite;

	sf::Vector2f crhRecoilDirection;
	sf::Vector2f crhOffset;
	sf::Vector2f myOffset;

	bool mousePressed;
	bool crhRecoilActive;
	bool recoilTimerActive;

	bool crhRecoilCalculated;
	bool crhRecoilUp;

	bool outOfControl;

	float random;
	float randomXSway;

	float crhRecoilSpeed;
	float crhRecoilDistance;

	float recoilCoolDownTime;
	float recoilCoolDown;

	float yPistolRecoil;
	float yPistolRecoilStrength;
	float yPistolRecoilStrengthTemp;
	float pistolRecoilMultiplier;

	int recoilType;

	int pistolClipSize;
	int pistolClip;

};

#endif 