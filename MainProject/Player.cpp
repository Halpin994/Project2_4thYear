#include "stdafx.h"
#include "SFML/Graphics.hpp"
#include <SFML/OpenGL.hpp>

#include <iostream>
#include "Math.h"
#include "Player.h"
#include "BulletManager.h"
#include "CollisionManager.h"
#include "SoundManager.h"

//! (Brief desc)
/*!
\(Detailed desc)
\return
\sa
*/
Player::Player()
{
	mousePressed = true;

	randomXSway = 0;
	crhOffset = sf::Vector2f(0, 0);
	recoilType = 2;

	crhRecoilActive = false;
	crhRecoilSpeed = 50;
	crhRecoilCalculated = false;
	crhRecoilUp = false;

	outOfControl = false;

	yPistolRecoilStrength = 5;
	yPistolRecoilStrengthTemp = yPistolRecoilStrength;
	yPistolRecoil = 0;
	pistolRecoilMultiplier = 1.8;
	recoilCoolDownTime = 0.4;
	recoilCoolDown = recoilCoolDownTime;

	pistolClipSize = 14;
	pistolClip = pistolClipSize;

	Load();
	SetUp();
}

Player::~Player()
{

}

//! Load in assets
/*!
\Loads in the crosshair image(s) and assigns it to texture crosshairImage
\return none
\sa
*/
void Player::Load()
{
	crosshairImage.loadFromFile("Assets/Images/Game/crosshair.png");
	clipBulletImage.loadFromFile("Assets/Images/Game/bullet.png");
}

//! Setup the player crosshair sprite
/*!
\Set the sprites origin to the centre of the sprite. Sets the texture for the sprite
\return none
\sa
*/
void Player::SetUp()
{
	crosshairSprite.setOrigin(75, 74);
	crosshairSprite.setTexture(crosshairImage, true);
	clipBulletSprite.setTexture(clipBulletImage, true);
}

//! Draw the player
/*!
\Draw the player's crosshair sprite relative to the window
\return none
\sa
*/
void Player::Draw(sf::RenderWindow& window)
{
	for (int i = 0; i < pistolClip; i++)
	{
		clipBulletSprite.setPosition(100 + i * 15, 650);
		window.draw(clipBulletSprite);
	}
	window.draw(crosshairSprite);

}

//! Update the Player
/*!
\Updates the player's crosshair position, creates a random X axis sway for the gun recoil(move to gun manager class later)
\Checks for a mouse click, allows the player to shoot and allows for the application of the recoil.
\return none
\sa
*/
void Player::Update(sf::RenderWindow& window, float frameTime)
{
	if (recoilTimerActive == true && recoilType == 2)
	{
		recoilCoolDown -= frameTime;
		if (recoilCoolDown <= 0)
		{
			yPistolRecoilStrengthTemp = yPistolRecoilStrength;
			yPistolRecoil = 0;
			recoilCoolDown = recoilCoolDownTime;
			outOfControl = false;
			recoilTimerActive = false;
		}
	}

	crosshairSprite.setPosition(sf::Mouse::getPosition(window).x + crhOffset.x, sf::Mouse::getPosition(window).y + crhOffset.y);

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		mousePressed = false;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mousePressed == false)
	{
		mousePressed = true;
		Shoot(window);
	}
	if (crhRecoilActive)
	{
		CrosshairRecoil(window, frameTime);
	}
}

//! Shoot bullets
/*!
\Draws a bullet hole at the crosshair position when the player shoots.
\This is done by passing a bullet hole type and the position of the crosshair.
\return none
\sa
*/
void Player::Shoot(sf::RenderWindow& window)
{
	//cout << "Shot Fired" << endl;
	if (pistolClip == 0){
		SoundManager::GetInstance()->PlayOutOfAmmo();
	}
	if (pistolClip > 0){
		pistolClip -= 1;
		SoundManager::GetInstance()->PlayPistolGunShot();
		if (recoilType == 1)
		{
			if (CollisionManager::GetInstance()->CheckTargetCollision(sf::Vector2f(crosshairSprite.getPosition().x, crosshairSprite.getPosition().y)) == true)
			{
				BulletManager::GetInstance()->AddBullets(2, crosshairSprite.getPosition());
			}
			else
				BulletManager::GetInstance()->AddBullets(1, crosshairSprite.getPosition());
		} //END Recoil Type 1
		if (recoilType == 2)
		{
			if (recoilCoolDown == recoilCoolDownTime)
			{
				if (CollisionManager::GetInstance()->CheckTargetCollision(sf::Vector2f(crosshairSprite.getPosition().x, crosshairSprite.getPosition().y)) == true)
				{
					BulletManager::GetInstance()->AddBullets(2, crosshairSprite.getPosition());
				}
				else
					BulletManager::GetInstance()->AddBullets(1, crosshairSprite.getPosition());
			}
			else if (recoilCoolDown < recoilCoolDownTime)
			{
				if (CollisionManager::GetInstance()->CheckTargetCollision(sf::Vector2f(crosshairSprite.getPosition().x, crosshairSprite.getPosition().y) + PistolBulletRecoil()) == true)
				{
					BulletManager::GetInstance()->AddBullets(2, crosshairSprite.getPosition() + sf::Vector2f(randomXSway, yPistolRecoil));
				}
				else
				{
					BulletManager::GetInstance()->AddBullets(1, crosshairSprite.getPosition() + sf::Vector2f(randomXSway, yPistolRecoil));
				}
				cout << "yRecoil: " << yPistolRecoil << endl;
			}
			if (recoilTimerActive == true && recoilType == 2)
			{
				recoilCoolDown = recoilCoolDownTime;
			}
			recoilTimerActive = true;
		} //END Recoil Type 2
		crhRecoilActive = true;
	}
}

//! Applys recoil to the crosshair sprite
/*!
\ Creates a recoil offset
\return none
\sa
*/
void Player::CrosshairRecoil(sf::RenderWindow& window, float frameTime)
{
	if (crhRecoilCalculated == false)
	{
		if (recoilType == 1)
		{
			/*float randomXSway = rand() % 1000;
			randomXSway = (randomXSway / 200) - 2.5;*/
			crhRecoilDirection = sf::Vector2f(getRandomSway().x, 5);
			Normalize(crhRecoilDirection); //Make recoilDirection a unit vector
			myOffset = crhRecoilDirection * crhRecoilSpeed * frameTime;
			crhRecoilCalculated = true;
		}
		if (recoilType == 2)
		{
			crhRecoilDirection = sf::Vector2f(0, 5);
			Normalize(crhRecoilDirection); //Make recoilDirection a unit vector
			myOffset = crhRecoilDirection * crhRecoilSpeed * frameTime;
			crhRecoilCalculated = true;
		}
	}

	if (recoilType == 1)
	{
		//if (offset.y > -20)
		if (getcrhRecoilDistance() < 10)
		{
			crhOffset.x += myOffset.x;
			crhOffset.y -= myOffset.y;
		}
		else
		{
			sf::Mouse::setPosition(sf::Vector2i(crosshairSprite.getPosition().x, crosshairSprite.getPosition().y), window);
			crhOffset = sf::Vector2f(0, 0);
			crhRecoilCalculated = false;
			crhRecoilActive = false;
			//recoilTime = 0;
		}
	}
	if (recoilType == 2)
	{
		if (getcrhRecoilDistance() < 10 && crhRecoilUp == false)
		{
			crhOffset.y -= myOffset.y;
			if (getcrhRecoilDistance() > 10)
			{
				crhRecoilUp = true;
			}
			//cout << "After offset: " << offset.y << endl;
		}
		if (crhRecoilUp == true)
		{
			crhOffset.y += myOffset.y;
		}
		if (crhRecoilUp == true && crhOffset.y >= 0)
		{
			//offset = sf::Vector2f(0, 0);
			crhRecoilUp = false;
			crhRecoilActive = false;
			crhRecoilCalculated = false;
			//recoilTime = 0;
		}
	}
}

sf::Vector2f Player::PistolBulletRecoil()
{
	sf::Vector2f rec;
	if (yPistolRecoil > -100 && outOfControl == false)
	{
		yPistolRecoilStrengthTemp *= pistolRecoilMultiplier;
		rec = sf::Vector2f(getRandomSway().x, yPistolRecoil -= yPistolRecoilStrengthTemp);
	}
	if (yPistolRecoil < -100 && outOfControl == false)
	{
		outOfControl = true;
		randomXSway = rand() % 1000;
		randomXSway = (randomXSway / 10) - 50;
		float randomYSway = rand() % 1000;
		randomYSway = (randomYSway / 50) - 10;
		rec = sf::Vector2f(randomXSway, yPistolRecoil += randomYSway);
	}
	else if (outOfControl == true)
	{
		randomXSway = rand() % 1000;
		randomXSway = (randomXSway / 10) - 50;
		float randomYSway = rand() % 1000;
		randomYSway = (randomYSway / 50) - 10;
		rec = sf::Vector2f(randomXSway, yPistolRecoil -= randomYSway);
	}

	return rec;
}

//! Normalize a vector passed on call
/*!
\When this method is called a vector of type float must be passed. This method then normalises it (creates a unit vector)
\return Vector2f
\sa
*/
sf::Vector2f Player::Normalize(sf::Vector2f NormaliseMe)
{
	float length;
	sf::Vector2f normalisedV(0, 0);
	length = sqrtf(powf(NormaliseMe.x, 2) + powf(NormaliseMe.y, 2));
	//cout << length << endl;
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
float Player::getVectorLength(sf::Vector2i vec)
{
	return sqrtf(powf(vec.x, 2) + powf(vec.y, 2));
}

float Player::getcrhRecoilDistance()
{
	crhRecoilDistance = sqrtf(powf(0 - crhOffset.x, 2) + powf(0 - crhOffset.y, 2));
	//cout << recoilDistance << endl;
	return crhRecoilDistance;
}

sf::Vector2f Player::getRandomSway()
{
	randomXSway = rand() % 1000;
	randomXSway = (randomXSway / 100) - 5;
	return sf::Vector2f(randomXSway, 0);
}

