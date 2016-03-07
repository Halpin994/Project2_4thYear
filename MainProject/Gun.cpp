#include "stdafx.h"
#include "Gun.h"
#include "SoundManager.h"
#include "BulletManager.h"
#include "CollisionManager.h"


Gun::Gun(int t)
{
	switch (t)
	{
	case PISTOL:
		clipSize = 12;
		currentClip = 12;
		recoilCooldownTime = 0.3;
		recoilCooldownTimer = 0;
		pistolImage.loadFromFile("Assets/Images/Game/Crosshairs/crosshair_pistol.png");
		crosshairSprite.setTexture(pistolImage);
	break;

	case SMG:
		clipSize = 30;
		currentClip = 30;
		recoilCooldownTime = 0.2;
		recoilCooldownTimer = 0;
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

void Gun::Shoot()
{
	if (currentClip == 0)
	{
		SoundManager::GetInstance()->PlayOutOfAmmo();
	}
	else if (currentClip > 0)
	{
		currentClip -= 1;
		SoundManager::GetInstance()->PlayPistolGunShot();
		
		if (recoilCooldownTimer == recoilCooldownTime)
		{
			if (!CollisionManager::GetInstance()->CheckTargetCollision(sf::Vector2f(crosshairSprite.getPosition().x, crosshairSprite.getPosition().y)))
			{
				BulletManager::GetInstance()->AddBullet(crosshairSprite.getPosition());
			}
		}
		else if (recoilCooldownTimer > 0)
		{
			if (!CollisionManager::GetInstance()->CheckTargetCollision(sf::Vector2f(crosshairSprite.getPosition().x, crosshairSprite.getPosition().y)))
			{

			}
		}
	}
}