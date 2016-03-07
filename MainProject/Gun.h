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

	void Shoot();
private:
	int clipSize;
	int currentClip;
	float recoilCooldownTime;
	float recoilCooldownTimer;
	sf::Texture pistolImage;
	sf::Texture smgImage;
	sf::Sprite crosshairSprite;
	
};
#endif 

