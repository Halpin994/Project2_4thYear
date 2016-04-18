#include "stdafx.h"
#include "SFML/Graphics.hpp"
#include <SFML/OpenGL.hpp>

#include <iostream>
#include "Math.h"
#include "Player.h"
#include "BulletManager.h"
#include "CollisionManager.h"
#include "SoundManager.h"
#include "GameStateManager.h"

//! (Brief desc)
/*!
\(Detailed desc)
\return
\sa
*/
Player::Player()
{
	quickReloadActive = false;
	normalReloadClicked = false;
	quickReloadClicked = false;

	leftMousePressed = true;

	quickReloadTime = 1.2;
	quickReloadTimer = quickReloadTime;

	normalReloadTime = 2.0;
	normalReloadTimer = normalReloadTime;

	gameTime = 0;
	gameOverTime = 0;

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
	//LoadCrosshair();
	clipBulletImage.loadFromFile("Assets/Images/Game/bullet.png");
	reloadQuickImage.loadFromFile("Assets/Images/Game/reloadQuick.png");
	reloadNormalImage.loadFromFile("Assets/Images/Game/reloadNormal.png");
	reloadUnavailableImage.loadFromFile("Assets/Images/Game/reloadUnavailable.png");
	pistolClipImage.loadFromFile("Assets/Images/Game/pistolClip.png");

	font.loadFromFile("Assets/imagine_font.ttf");
}

//! Setup the player crosshair sprite
/*!
\Set the sprites origin to the centre of the sprite. Sets the texture for the sprite
\return none
\sa
*/
void Player::SetUp()
{
	AddGun(Gun::PISTOL);
	AddGun(Gun::SMG);
	currentGun = guns[Gun::SMG];

	clipBulletSprite.setTexture(clipBulletImage, true);

	reloadNormalSprite.setTexture(reloadNormalImage, true);
	reloadQuickSprite.setTexture(reloadQuickImage, true);
	reloadUnavailableSprite.setTexture(reloadUnavailableImage, true);

	reloadNormalSprite.setPosition(600 - reloadNormalSprite.getGlobalBounds().width/2, 650);
	reloadQuickSprite.setPosition(600 - reloadQuickSprite.getGlobalBounds().width / 2, 650);
	reloadUnavailableSprite.setPosition(600 - reloadQuickSprite.getGlobalBounds().width / 2, 650);

	pistolClipSprite.setTexture(pistolClipImage, true);
	pistolClipSprite.setPosition(173, 648);

	gunClipText.setFont(font);
	gunClipText.setCharacterSize(50);
	gunClipText.setPosition(100, 635);
	gunClipText.setColor(sf::Color::Yellow);
}

void Player::AddGun(int type)
{
	guns[type] = new Gun(type);
}

//! Draw the player
/*!
\Draw the player's crosshair sprite relative to the window
\return none
\sa
*/
void Player::Draw(sf::RenderWindow& window)
{
	for (int i = 0; i < currentGun->getCurrentClip(); i++)
	{
		if (currentGun->getShotFired())
		{
			clipBulletSprite.setPosition(182 + i * 12, 650); //offset to less than the bullet width to create the illusion of the bullets moving up the clip
			window.draw(clipBulletSprite);
		}
		else
		{
			clipBulletSprite.setPosition(175 + i * 12, 650);
			window.draw(clipBulletSprite);
		}
	}

	//window.draw(pistolClipSprite);
	window.draw(gunClipText);
	currentGun->Draw(window);

	//if (pistolClip == pistolClipSize || normalReloadClicked == true)
	//{
	//	window.draw(reloadUnavailableSprite);
	//}
	//if (normalReloadClicked == false && quickReloadActive == false && pistolClip < pistolClipSize)
	//{
	//	window.draw(reloadNormalSprite);
	//}
	//if (quickReloadActive == true)
	//{
	//	window.draw(reloadQuickSprite);
	//}

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
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		leftMousePressed = false;
	}
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		rightMousePressed = false;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && leftMousePressed == false)
	{
		currentGun->Shoot();
		if (currentGun->getGunType() == Gun::PISTOL)
		{
			leftMousePressed = true;
		}
	}

	currentGun->Update(window, frameTime);
	ss.str(std::string());
	
	ss << currentGun->getCurrentClip();
	gunClipText.setString(ss.str());
	
	/*if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && leftMousePressed == false && normalReloadClicked == false)
	{
		if (currentCrosshair != Crosshairs::smg)
		{
			leftMousePressed = true;
		}
		if (CollisionManager::GetInstance()->CheckReloadCollision(crosshairSprite.getPosition(), reloadNormalSprite.getPosition(), reloadNormalSprite.getGlobalBounds()) == true)
		{
			if (pistolClip < pistolClipSize)
			{
				if (quickReloadActive == true)
				{
					SoundManager::GetInstance()->PlayPistolQuickReload();
					Reload();
					quickReloadClicked = true;
				}
				else if (quickReloadActive == false)
				{
					SoundManager::GetInstance()->PlayPistolReload();
					normalReloadClicked = true;
				}
			}
		}
		else
		{
			if (currentCrosshair != Crosshairs::smg)
			{
				Shoot(window);
			}
			else if (smgFireRateTimer < 0)
			{
				Shoot(window);
				smgFireRateTimer = smgFireRate;
			}
				
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		if (pistolClip < pistolClipSize)
		{
			if (quickReloadActive == true)
			{
				SoundManager::GetInstance()->PlayPistolQuickReload();
				quickReloadClicked = true;
				Reload();
			}
			else if (quickReloadActive == false)
			{
				SoundManager::GetInstance()->PlayPistolReload();
				normalReloadClicked = true;
			}
		}
	}

	if (crhRecoilActive)
	{
		CrosshairRecoil(window, frameTime);
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && rightMousePressed == false)
	{
		rightMousePressed = true;
		if (currentCrosshair == Crosshairs::smg)
		{
			currentCrosshair = Crosshairs::pistol;
			LoadCrosshair();
		}
		else if (currentCrosshair == Crosshairs::pistol)
		{
			currentCrosshair = Crosshairs::greenHalfCirc;
			LoadCrosshair();
		}
		else if (currentCrosshair == crosshairType)
		{
			currentCrosshair = Crosshairs::smg;
			LoadCrosshair();
		}
	}*/
}

void Player::Restart()
{
	//pistolClip = pistolClipSize;
	
}

void Player::Reload()
{
	//pistolClip = pistolClipSize;
	quickReloadTimer = quickReloadTime;
	normalReloadTimer = normalReloadTime;
	quickReloadActive = false;
	normalReloadClicked = false;
}

void Player::UpdateReloadTimes(float frameTime)
{
	/*if (recoilTimerActive == true && recoilType == 2)
	{
		recoilCoolDown -= frameTime;
		if (recoilCoolDown <= 0)
		{
			yPistolRecoilStrengthTemp = yPistolRecoilStrength;
			yPistolRecoil = 0;
			recoilCoolDown = pistolRecoilCoolDownTime;
			outOfControl = false;
			recoilTimerActive = false;
		}
	}

	if (pistolClip == 0 && quickReloadTimer > 0)
	{
		quickReloadTimer -= frameTime;
		quickReloadActive = true;
		if (quickReloadTimer < 0)
		{
			quickReloadTimer = 0;
			quickReloadActive = false;
		}
	}
	if (normalReloadClicked == true)
	{
		normalReloadTimer -= frameTime;
		if (normalReloadTimer < 0)
		{
			Reload();
		}
	}*/
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
}

//! Applys recoil to the crosshair sprite
/*!
\ Creates a recoil offset
\return none
\sa
*/
void Player::CrosshairRecoil(sf::RenderWindow& window, float frameTime)
{
}

Gun* Player::getCurrentGun()
{
	return currentGun;
}

////! Normalize a vector passed on call
///*!
//\When this method is called a vector of type float must be passed. This method then normalises it (creates a unit vector)
//\return Vector2f
//\sa
//*/
//sf::Vector2f Player::Normalize(sf::Vector2f NormaliseMe)
//{
//	float length;
//	sf::Vector2f normalisedV(0, 0);
//	length = sqrtf(powf(NormaliseMe.x, 2) + powf(NormaliseMe.y, 2));
//	if (length != 0)
//	{
//		normalisedV = sf::Vector2f(NormaliseMe.x / length, NormaliseMe.y / length);
//	}
//	return normalisedV;
//}
//
////! Returns a vector's length
///*!
//\When called, this method must be passed a vector of type int. It then calculates the length of this vector
//\This is currently not used/needed
//\return float
//\sa
//*/
//float Player::getVectorLength(sf::Vector2i vec)
//{
//	return sqrtf(powf(vec.x, 2) + powf(vec.y, 2));
//}
//
//float Player::getcrhRecoilDistance()
//{
//	crhRecoilDistance = sqrtf(powf(0 - crhOffset.x, 2) + powf(0 - crhOffset.y, 2));
//	return crhRecoilDistance;
//}

//sf::Vector2f Player::getRandomSway()
//{
//	randomXSway = rand() % 1000;
//	randomXSway = (randomXSway / 100) - 5;
//	return sf::Vector2f(randomXSway, 0);
//}

int Player::getClipCount()
{
	return currentGun->getCurrentClip();
}

int Player::getMaxClip()
{
	return currentGun->getMaxClip();
}

bool Player::getLeftClicked()
{
	return leftMousePressed;
}

bool Player::getNormReloadClicked()
{
	return normalReloadClicked;
}

bool Player::getQuickReloadClicked()
{
	return quickReloadClicked;
}

