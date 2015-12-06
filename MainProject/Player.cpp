#include "stdafx.h"
#include "SFML/Graphics.hpp"
#include <SFML/OpenGL.hpp>

#include <iostream>
#include "Math.h"
#include "Player.h"
#include "BulletManager.h"
#include "Target.h"
#include "CollisionManager.h"
#include "SoundManager.h"

Target target;

//! (Brief desc)
/*!
\(Detailed desc)
\return
\sa
*/
Player::Player()
{
	mousePressed = true;
	recoilActive = false;
	recoilSpeed = 50;
	recoilTime = 0;
	offset = sf::Vector2f(0, 0);
	recoilType = 2;
	recoilCalculated = false;
	recoilUp = false;
	recoilCoolDownTime = 0.4;
	recoilCoolDown = recoilCoolDownTime;

	yRecoilStrength = 5;
	yRecoilStrengthTemp = yRecoilStrength;
	yRecoil = yRecoilStrengthTemp;
	randomXSway = 0;
	

	Load();
	SetUp();
}

Player::~Player()
{

}

////! Initialise the player position
///*!
//\Initialise the crosshair position to the centre of the window
//\return none
//\sa
//*/
//void Player::Init(sf::RenderWindow& window)
//{
//	crosshairSprite.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
//}

//! Load in assets
/*!
\Loads in the crosshair image(s) and assigns it to texture crosshairImage
\return none
\sa
*/
void Player::Load()
{
	crosshairImage.loadFromFile("Assets/Images/Game/crosshair.png");
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
}

//! Draw the player
/*!
\Draw the player's crosshair sprite relative to the window
\return none
\sa
*/
void Player::Draw(sf::RenderWindow& window)
{
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
		//cout << recoilCoolDown << endl;
		if (recoilCoolDown <= 0)
		{
			yRecoilStrengthTemp = yRecoilStrength;
			yRecoil = 0;
			recoilCoolDown = recoilCoolDownTime;
			recoilTimerActive = false;
		}
	}
	//float randomYSway = rand() % 1000;
	//randomYSway = (randomYSway / 200) - 2.5;


	//if (sf::Mouse::getPosition(window).x > 175 && sf::Mouse::getPosition(window).x < 1030 && sf::Mouse::getPosition(window).y < 590)
	//{
	//	crosshairSprite.setPosition(sf::Mouse::getPosition(window).x + offset.x, sf::Mouse::getPosition(window).y + offset.y);
	//}

	crosshairSprite.setPosition(sf::Mouse::getPosition(window).x + offset.x, sf::Mouse::getPosition(window).y + offset.y);

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		mousePressed = false;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mousePressed == false)
	{
		mousePressed = true;
		Shoot(window);
	}
	if (recoilActive)
	{
		Recoil(window, frameTime);
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
	SoundManager::GetInstance()->PlayPistolGunShot();
	if (recoilType == 1)
	{
		if (CollisionManager::GetInstance()->CheckTargetCollision(sf::Vector2f(crosshairSprite.getPosition().x, crosshairSprite.getPosition().y)) == true)
		{
			BulletManager::GetInstance()->AddBullets(2, crosshairSprite.getPosition());
		}
		else
			BulletManager::GetInstance()->AddBullets(1, crosshairSprite.getPosition());
	}
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
			if (CollisionManager::GetInstance()->CheckTargetCollision(sf::Vector2f(crosshairSprite.getPosition().x, crosshairSprite.getPosition().y) + sf::Vector2f(getRandomSway().x, yRecoil -= yRecoilStrengthTemp)) == true)
			{
				BulletManager::GetInstance()->AddBullets(2, crosshairSprite.getPosition() + sf::Vector2f(randomXSway, yRecoil));
			}
			else
			{
				BulletManager::GetInstance()->AddBullets(1, crosshairSprite.getPosition() + sf::Vector2f(randomXSway, yRecoil));
			}
			yRecoilStrengthTemp *= 1.25;
			cout << "yRecoil: " << yRecoil << endl;
		}
	}

	if (recoilTimerActive == true && recoilType == 2)
	{
		recoilCoolDown = recoilCoolDownTime;
	}
	recoilActive = true;
	recoilTimerActive = true;
}

//! Applys recoil to the crosshair sprite
/*!
\ Creates a recoil offset
\return none
\sa
*/
void Player::Recoil(sf::RenderWindow& window, float frameTime)
{
	if (recoilCalculated == false)
	{
		if (recoilType == 1)
		{
			/*float randomXSway = rand() % 1000;
			randomXSway = (randomXSway / 200) - 2.5;*/
			recoilDirection = sf::Vector2f(getRandomSway().x, 5);
			Normalize(recoilDirection); //Make recoilDirection a unit vector
			myOffset = recoilDirection * recoilSpeed * frameTime;
			recoilCalculated = true;
		}
		if (recoilType == 2)
		{
			recoilDirection = sf::Vector2f(0, 5);
			Normalize(recoilDirection); //Make recoilDirection a unit vector
			myOffset = recoilDirection * recoilSpeed * frameTime;
			recoilCalculated = true;
		}
	}

	if (recoilType == 1)
	{
		//if (offset.y > -20)
		if (getRecoilDistance() < 10)
		{
			offset.x += myOffset.x;
			offset.y -= myOffset.y;
		}
		else
		{
			sf::Mouse::setPosition(sf::Vector2i(crosshairSprite.getPosition().x, crosshairSprite.getPosition().y), window);
			offset = sf::Vector2f(0, 0);
			recoilCalculated = false;
			recoilActive = false;
			recoilTime = 0;
		}
	}
	if (recoilType == 2)
	{
		if (getRecoilDistance() < 10 && recoilUp == false)
		{
			offset.y -= myOffset.y;
			if (getRecoilDistance() > 10)
			{
				recoilUp = true;
			}
			//cout << "After offset: " << offset.y << endl;
		}
		if (recoilUp == true)
		{
			offset.y += myOffset.y;
		}
		if (recoilUp == true && offset.y >= 0)
		{
			//offset = sf::Vector2f(0, 0);
			recoilUp = false;
			recoilActive = false;
			recoilCalculated = false;
			recoilTime = 0;
		}
	}
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

float Player::getRecoilDistance()
{
	recoilDistance = sqrtf(powf(0 - offset.x, 2) + powf(0 - offset.y, 2));
	//cout << recoilDistance << endl;
	return recoilDistance;
}

sf::Vector2f Player::getRandomSway()
{
	randomXSway = rand() % 1000;
	randomXSway = (randomXSway / 100) - 5;
	return sf::Vector2f(randomXSway, 0);
}

