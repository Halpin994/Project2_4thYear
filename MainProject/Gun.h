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

	void Update(sf::RenderWindow& window, float frameTime);
	void Draw(sf::RenderWindow& window);

	sf::Vector2f BulletRecoil();
	void UpdateCrosshairRecoil();

	void Shoot();

	void UpdateBulletRecoilValues(float);

	void CalculateCrosshairRecoil(sf::RenderWindow& window, float frameTime);

	sf::Vector2f Normalize(sf::Vector2f);
	float getVectorLength(sf::Vector2i);
	float getcrhRecoilDistance();

	int getCurrentClip();
	int getMaxClip();
	bool getShotFired();
	int getGunType();

	void Gun::Reload();

	sf::Vector2f getGunPos();
private:
	int clipSize;
	int current_Clip;
	float recoilCooldownTime;
	float recoilCooldownTimer;
	float yStrength;
	float yRecoilStrength;
	float yRecoil;
	float yRecoilMax;
	float recoilMultiplier;

	float fireRate;
	float fireRateTimer;

	float reloadTime;
	float reloadTimer;

	float crhRecoilSpeed;
	float crhRecoilDistance;
	float crhRecoilMax;

	float scale;

	sf::Vector2f crhRecoilDirection;
	sf::Vector2f crhOffset;
	sf::Vector2f myOffset;

	float myScale;
	float scaleSpeed;
	float scaleDefault;

	int gunType;

	sf::Texture pistolImage;
	sf::Texture smgImage;
	sf::Sprite crosshairSprite;

	float outOfControlXMax;
	float outOfControlXMin;
	float outOfControlYMax;
	float outOfControlYMin;

	bool outOfControl;
	bool recoilActive;
	bool shotFired;
	bool crosshair_RecoilActive;
	bool crosshair_RecoilCalculated;
	bool crhRecoilUp;
	bool updateFireRate;
	
};
#endif 

