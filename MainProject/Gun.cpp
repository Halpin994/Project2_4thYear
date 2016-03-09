#include "stdafx.h"
#include "Gun.h"
#include "SoundManager.h"
#include "BulletManager.h"
#include "CollisionManager.h"


Gun::Gun(int type)
{
	outOfControl = false;
	recoilActive = false;
	shotFired = false;
	crosshair_RecoilActive = false;
	crosshair_RecoilCalculated = false;
	crhRecoilUp = false;
		
	crosshairSprite.setOrigin(75, 75);

	switch (type)
	{
	case PISTOL:
		gunName = "Pistol";
		clipSize = 112;
		current_Clip = clipSize;
		recoilCooldownTime = 0.3;
		recoilCooldownTimer = 0;
		recoilMultiplier = 1.5;
		yStrength = 10;
		yRecoilStrength = yStrength;
		yRecoil = 0;
		yRecoilMax = 120;
		fireRate = 0;
		fireRateTimer = 0;
		reloadTime = 2.0;
		reloadTimer = 0;
		pistolImage.loadFromFile("Assets/Images/Game/Crosshairs/crosshair_pistol.png");
		scale = 4;
		crosshairSprite.setScale(scale, scale);
		crosshairSprite.setTexture(pistolImage); 
		crhRecoilSpeed = 150;
		crhRecoilDirection = sf::Vector2f(0, 1);
		crhRecoilMax = 12;
		crhOffset = sf::Vector2f(0, 0);
	break;

	case SMG:
		gunName = "SMG";
		clipSize = 30;
		current_Clip = clipSize;
		recoilCooldownTime = 0.2;
		recoilCooldownTimer = 0;
		recoilMultiplier = 2.0;
		yStrength = 5;
		yRecoilStrength = yStrength;
		yRecoil = 0;
		yRecoilMax = 100;
		fireRate = 0.08;
		fireRateTimer = 0;
		reloadTime = 2.0;
		reloadTimer = 0;
		smgImage.loadFromFile("Assets/Images/Game/Crosshairs/crosshair_smg.png");
		scale = 4;
		crosshairSprite.setScale(scale, scale);
		crosshairSprite.setOrigin(sf::Vector2f(75.5, 75));
		crosshairSprite.setTexture(smgImage);
		crhRecoilSpeed = 150;
		crhRecoilDirection = sf::Vector2f(0, 1);
		crhRecoilMax = 100;
		crhOffset = sf::Vector2f(0, 0);
	break;
	}
}


Gun::~Gun()
{
}

void Gun::Update(sf::RenderWindow& window, float frameTime)
{
	cout << frameTime << endl;
	if (crosshair_RecoilActive)
	{
		CalculateCrosshairRecoil(window, frameTime);
		UpdateCrosshairRecoil();
	}
	UpdateBulletRecoilValues(frameTime);
	crosshairSprite.setPosition(sf::Mouse::getPosition(window).x + crhOffset.x, sf::Mouse::getPosition(window).y + crhOffset.y);
}

void Gun::Draw(sf::RenderWindow& window)
{
	window.draw(crosshairSprite);
}

void Gun::Shoot()
{
	crhOffset = sf::Vector2f(0, 0);
	crhRecoilUp = false;

	recoilActive = true;
	shotFired = true;
	crosshair_RecoilActive = true;

	//If the current gun clip is empty play the out of ammo sound
	if (current_Clip == 0)
	{
		SoundManager::GetInstance()->PlayOutOfAmmo();
	}
	//If the current gun clip is not empty, take 1 from the clip, play the shoot sfx, check target collision, if no target collision adda bullet at the position fired
	else if (current_Clip > 0)
	{
		current_Clip -= 1;
		SoundManager::GetInstance()->PlayPistolGunShot();

		if (recoilCooldownTimer == 0)
		{
			if (!CollisionManager::GetInstance()->CheckTargetCollision(sf::Vector2f(crosshairSprite.getPosition().x, crosshairSprite.getPosition().y)))
			{
				BulletManager::GetInstance()->AddBullet(crosshairSprite.getPosition());
			}
		}
		else if (recoilCooldownTimer > 0)
		{
			sf::Vector2f recoil = BulletRecoil();
			if (!CollisionManager::GetInstance()->CheckTargetCollision(sf::Vector2f(crosshairSprite.getPosition().x, crosshairSprite.getPosition().y) + recoil))
			{
				BulletManager::GetInstance()->AddBullet(crosshairSprite.getPosition() + recoil);//+ //sf::Vector2f(randomXSway, yPistolRecoil));
			}
		}
	}
}

sf::Vector2f Gun::BulletRecoil()
{
	sf::Vector2f rec;
	if (outOfControl == false)
	{
		yRecoilStrength *= recoilMultiplier;
		yRecoil -= yRecoilStrength;
		rec = sf::Vector2f(0, yRecoil);
	}
	if (yRecoil < -yRecoilMax && outOfControl == false)
	{
		outOfControl = true;
	}
	if (outOfControl == true)
	{
		float randomXSway = rand() % 1000;
		randomXSway = (randomXSway / 10) - 50;
		float randomYSway = rand() % 1000;
		randomYSway = (randomYSway / 50) - 10;
		rec = sf::Vector2f(randomXSway, yRecoil -= randomYSway);
	}
	return rec;
}

void Gun::UpdateBulletRecoilValues(float ft)
{
	if (shotFired)
	{
		recoilCooldownTimer = 0;
		shotFired = false;
	}
	if (recoilActive)
	{
		recoilCooldownTimer += ft;
		if (recoilCooldownTimer >= recoilCooldownTime)
		{
			recoilActive = false;
			recoilCooldownTimer = 0;
			yRecoil = 0;
			yRecoilStrength = yStrength;
			outOfControl = false;
		}
	}
}

void Gun::CalculateCrosshairRecoil(sf::RenderWindow& window, float frameTime)
{
	Normalize(crhRecoilDirection); //Make recoilDirection a unit vector
	myOffset = crhRecoilDirection * crhRecoilSpeed * frameTime;
	crosshair_RecoilCalculated = true;
}

void Gun::UpdateCrosshairRecoil()
{
	if (crhRecoilUp == true && getcrhRecoilDistance() <= 5)
	{
		crhOffset = sf::Vector2f(0, 0);
		crhRecoilUp = false;
		crosshair_RecoilActive = false;
	}
	if (getcrhRecoilDistance() < crhRecoilMax && crhRecoilUp == false)
	{
		crhOffset.x += myOffset.x;
		crhOffset.y -= myOffset.y;
		if (getcrhRecoilDistance() > crhRecoilMax)
		{
			crhRecoilUp = true;
		}
	}
	else if (crhRecoilUp == true)
	{
		crhOffset.x -= myOffset.x;
		crhOffset.y += myOffset.y;
	}
}

//! Normalize a vector passed on call
/*!
\When this method is called a vector of type float must be passed. This method then normalises it (creates a unit vector)
\return Vector2f
\sa
*/
sf::Vector2f Gun::Normalize(sf::Vector2f NormaliseMe)
{
	float length;
	sf::Vector2f normalisedV(0, 0);
	length = sqrtf(powf(NormaliseMe.x, 2) + powf(NormaliseMe.y, 2));
	if (length != 0)
	{
		normalisedV = sf::Vector2f(NormaliseMe.x / length, NormaliseMe.y / length);
	}
	return normalisedV;
}

//! Returns a vector's length
/*!
\When called, this method must be passed a vector of type int. It then calculates the length of this vector
\This is currently not used/needed
\return float
\sa
*/
float Gun::getVectorLength(sf::Vector2i vec)
{
	return sqrtf(powf(vec.x, 2) + powf(vec.y, 2));
}

float Gun::getcrhRecoilDistance()
{
	crhRecoilDistance = sqrtf(powf(0 - crhOffset.x, 2) + powf(0 - crhOffset.y, 2));
	return crhRecoilDistance;
}

int Gun::getCurrentClip()
{
	return current_Clip;
}

int Gun::getMaxClip()
{
	return clipSize;
}