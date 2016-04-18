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
		gunType = PISTOL;
		clipSize = 20;
		current_Clip = clipSize;
		recoilCooldownTime = 0.7;
		recoilCooldownTimer = 0;
		recoilMultiplier = 1.2;
		yStrength = 5;
		yRecoilStrength = yStrength;
		yRecoil = 0;
		yRecoilMax = 50;
		fireRate = 0;
		fireRateTimer = 0;
		reloadTime = 2.0;
		reloadTimer = 0;
		pistolImage.loadFromFile("Assets/Images/Game/Crosshairs/crosshair_pistol.png");
		scaleDefault = 4;
		scale = scaleDefault;
		scaleSpeed = 5;
		crosshairSprite.setScale(scale, scale);
		crosshairSprite.setTexture(pistolImage); 
		crhRecoilSpeed = 150;
		crhRecoilDirection = sf::Vector2f(0, 1);
		crhRecoilMax = -8;
		crhOffset = sf::Vector2f(0, 0);
	break;

	case SMG:
		gunType = SMG;
		clipSize = 130;
		current_Clip = clipSize;
		recoilCooldownTime = 0.5;
		recoilCooldownTimer = 0;
		recoilMultiplier = 1.2;
		yStrength = 2;
		yRecoilStrength = yStrength;
		yRecoil = 0;
		yRecoilMax = 50;
		fireRate = 0.12;
		fireRateTimer = 0;
		reloadTime = 2.0;
		reloadTimer = 0;
		smgImage.loadFromFile("Assets/Images/Game/Crosshairs/crosshair_smg.png");
		scaleDefault = 4;
		scale = scaleDefault;
		scaleSpeed = 15;
		crosshairSprite.setScale(scale, scale);
		crosshairSprite.setOrigin(sf::Vector2f(75.5, 75));
		crosshairSprite.setTexture(smgImage);
		crhRecoilSpeed = 350;
		crhRecoilDirection = sf::Vector2f(0, 1);
		crhRecoilMax = -10;
		crhOffset = sf::Vector2f(0, 0);
		updateFireRate = false;
	break;
	}
}


Gun::~Gun()
{
}

void Gun::Update(sf::RenderWindow& window, float frameTime)
{
	if (updateFireRate)
	{
		fireRateTimer += frameTime;
	}
	//cout << frameTime << endl;
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
	//crhOffset = sf::Vector2f(0, 0);
	//crhRecoilUp = false;
	updateFireRate = true;

	//If the current gun clip is not empty, take 1 from the clip, play the shoot sfx, check target collision, if no target collision adda bullet at the position fired
	if (current_Clip > 0 && fireRateTimer >= fireRate)
	{
		fireRateTimer = 0;
		//updateFireRate = false;
			
		recoilActive = true;
		shotFired = true;
		crosshair_RecoilActive = true;

		current_Clip -= 1;
		SoundManager::GetInstance()->PlayPistolGunShot();
		SoundManager::GetInstance()->PlayFallingShell();

		if (recoilCooldownTimer == 0)
		{
			if (!CollisionManager::GetInstance()->CheckTargetCollision(sf::Vector2f(crosshairSprite.getPosition().x, crosshairSprite.getPosition().y), gunType))
			{
				BulletManager::GetInstance()->AddBullet(crosshairSprite.getPosition(), gunType);
			}
		}
		else if (recoilCooldownTimer > 0)
		{
			sf::Vector2f recoil = BulletRecoil();
			if (!CollisionManager::GetInstance()->CheckTargetCollision(sf::Vector2f(crosshairSprite.getPosition().x, crosshairSprite.getPosition().y) + recoil, gunType))
			{
				BulletManager::GetInstance()->AddBullet(crosshairSprite.getPosition() + recoil, gunType);//+ //sf::Vector2f(randomXSway, yPistolRecoil));
			}
		}
	}
	//If the current gun clip is empty play the out of ammo sound
	else if (current_Clip == 0)
	{
		SoundManager::GetInstance()->PlayOutOfAmmo();
	}
}

sf::Vector2f Gun::BulletRecoil()
{
	sf::Vector2f rec;
	if (yRecoil < -yRecoilMax && outOfControl == false)
	{
		outOfControl = true;
	}
	if (outOfControl == false)
	{
		//yRecoilStrength = recoilMultiplier;
		yRecoilStrength *= recoilMultiplier;
		yRecoil -= yRecoilStrength * (recoilCooldownTime / recoilCooldownTimer);
		rec = sf::Vector2f(0, yRecoil);
		
	}
	else if (outOfControl == true)
	{
		outOfControlXMax = -25;
		outOfControlXMin = 25;
		outOfControlYMax = -2;
		outOfControlYMin = -50;

		//float randomXSway = rand() % 1000;
		//randomXSway = (randomXSway / 10) - 50;
		//float randomXSway = rand() % (outOfControlXMax - (outOfControlXMin)) + (outOfControlXMin);
		//(float(rand()) / float(RAND_MAX)) * (Max - Min)) + Min;
		float randomXSway = ((float(rand()) / float(RAND_MAX)) * (outOfControlXMax - outOfControlXMin)) + outOfControlXMin;
		//float randomYSway = rand() % 1000;
		//randomYSway = (randomYSway / 50) - 10;
		//float randomYSway = rand() % (outOfControlYMax - (outOfControlYMin)) + (outOfControlYMin);
		float randomYSway = ((float(rand()) / float(RAND_MAX)) * (outOfControlYMax - outOfControlYMin)) + outOfControlYMin;
		cout << randomYSway << endl;
		//randomYSway = randomYSway / 100;
		rec = sf::Vector2f(randomXSway, yRecoil + randomYSway);
	}
	return rec;
}

void Gun::UpdateBulletRecoilValues(float ft)
{
	if (shotFired)
	{
		shotFired = false;
		recoilCooldownTimer = 0;
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
	myScale = scaleSpeed * frameTime;
	crosshair_RecoilCalculated = true;
}

void Gun::UpdateCrosshairRecoil()
{

	if (crhOffset.y > crhRecoilMax && crhRecoilUp == false)
	{
		scale += myScale;
		crhOffset.x += myOffset.x;
		crhOffset.y -= myOffset.y;
		if (crhOffset.y < crhRecoilMax)
		{
			crhRecoilUp = true;
		}
		crosshairSprite.setScale(scale, scale);
	}
	else if (crhRecoilUp == true && crhOffset.y > 0)
	{
		crhOffset = sf::Vector2f(0, 0);
		crhRecoilUp = false;
		scale = scaleDefault;
		crosshair_RecoilActive = false;
		crosshairSprite.setScale(scale, scale);
	}
	else if (crhRecoilUp == true)
	{
		scale -= myScale;
		crhOffset.x -= myOffset.x;
		crhOffset.y += myOffset.y;
		crosshairSprite.setScale(scale, scale);
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

bool Gun::getShotFired()
{
	return crosshair_RecoilActive;
}

int Gun::getGunType()
{
	return gunType;
}

sf::Vector2f Gun::getGunPos()
{
	return crosshairSprite.getPosition();
}