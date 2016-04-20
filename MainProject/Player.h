#include <iostream>
using namespace std;

//#include "SFML\Audio.hpp"
#include <map>
#include <sstream>
#include "Gun.h"

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

	void AddGun(int);

	void Draw(sf::RenderWindow& window);
	void Player::DrawResult(sf::RenderWindow& window);
	void Shoot(sf::RenderWindow& window);
	void CrosshairRecoil(sf::RenderWindow& window, float);
	sf::Vector2f Player::PistolBulletRecoil();
	void Update(sf::RenderWindow& window, float);
	sf::Vector2f Normalize(sf::Vector2f);
	float getVectorLength(sf::Vector2i vec);
	float Player::getcrhRecoilDistance();
	sf::Vector2f Player::getRandomSway();
	void Player::CreateGunClip();
	void Player::Reload();
	void Player::UpdateReloadTimes(float);
	void Player::LoadCrosshair();
	void Player::Restart();

	int Player::getClipCount();
	int Player::getMaxClip();
	bool Player::getLeftClicked();
	bool Player::getNormReloadClicked();
	bool Player::getQuickReloadClicked();

	Gun* Player::getCurrentGun();

private:
	sf::Texture clipBulletImage;
	sf::Sprite clipBulletSprite;
	sf::Texture pistolClipImage;
	sf::Sprite pistolClipSprite;

	sf::Texture reloadQuickImage;
	sf::Sprite reloadQuickSprite;
	sf::Texture reloadNormalImage;
	sf::Sprite reloadNormalSprite;
	sf::Texture reloadUnavailableImage;
	sf::Sprite reloadUnavailableSprite;

	bool rightMousePressed;
	bool leftMousePressed;

	bool quickReloadActive;
	bool quickReloadClicked;
	bool normalReloadClicked;

	float quickReloadTime;
	float quickReloadTimer;

	float normalReloadTime;
	float normalReloadTimer;

	float gameTime;
	float gameOverTime;

	sf::Font font;
	sf::Text gunClipText;
	std::stringstream ss;

	map<int, Gun*> guns;
	Gun* currentGun;
};

#endif 