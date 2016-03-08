#ifndef GUN
#define GUN

#include "SFML/Graphics.hpp"
#include <SFML/OpenGL.hpp>

class Gun
{
public:
	Gun(int type);
	~Gun();
	static const int REDCIRCLECROSS = 0, GREENHALFCIRC = 1, PISTOL = 2, SMG = 3;

	void Update(sf::RenderWindow& window);
	void Draw(sf::RenderWindow& window);

	sf::Vector2f Gun::BulletRecoil();

	void Shoot();

	int getCurrentClip();
	int getMaxClip();
private:
	int clipSize;
	int current_Clip;
	float recoilCooldownTime;
	float recoilCooldownTimer;
	float yRecoilStrength;
	float yRecoil;
	float recoilMultiplier;

	float fireRate;
	float fireRateTimer;

	float reloadTime;
	float reloadTimer;

	sf::String gunName;

	sf::Texture pistolImage;
	sf::Texture smgImage;
	sf::Sprite crosshairSprite;

	bool outOfControl;
	
};
#endif 

