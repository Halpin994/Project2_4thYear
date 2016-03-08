#include "stdafx.h"
#include "Gun.h"
#include "SoundManager.h"
#include "BulletManager.h"
#include "CollisionManager.h"


Gun::Gun(int type)
{
	outOfControl = false;
	crosshairSprite.setOrigin(75, 75);

	switch (type)
	{
	case PISTOL:
		gunName = "Pistol";
		clipSize = 12;
		current_Clip = clipSize;
		recoilCooldownTime = 0.3;
		recoilCooldownTimer = 0;
		recoilMultiplier = 1.8;
		yRecoilStrength = 5;
		yRecoil = 0;
		fireRate = 0;
		fireRateTimer = 0;
		reloadTime = 2.0;
		reloadTimer = 0;
		pistolImage.loadFromFile("Assets/Images/Game/Crosshairs/crosshair_pistol.png");
		crosshairSprite.setTexture(pistolImage);
	break;

	case SMG:
		gunName = "SMG";
		clipSize = 30;
		current_Clip = clipSize;
		recoilCooldownTime = 0.2;
		recoilCooldownTimer = 0;
		recoilMultiplier = 2.0;
		yRecoilStrength = 5;
		yRecoil = 0;
		fireRate = 0.08;
		fireRateTimer = 0;
		reloadTime = 2.0;
		reloadTimer = 0;
		smgImage.loadFromFile("Assets/Images/Game/Crosshairs/crosshair_smg.png");
		crosshairSprite.setTexture(smgImage);
	break;
	}
}


Gun::~Gun()
{
}

void Gun::Update(sf::RenderWindow& window)
{
	crosshairSprite.setPosition(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);
}

void Gun::Draw(sf::RenderWindow& window)
{
	window.draw(crosshairSprite);
}

void Gun::Shoot()
{
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
		rec = sf::Vector2f(0,yRecoil -= yRecoilStrength);
	}
	if (yRecoilStrength < -100 && outOfControl == false)
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

int Gun::getCurrentClip()
{
	return current_Clip;
}

int Gun::getMaxClip()
{
	return clipSize;
}