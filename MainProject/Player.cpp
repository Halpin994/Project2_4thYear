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
	leftMousePressed = true;
	rightMousePressed = true;

	//randomXSway = 0;
	//crhOffset = sf::Vector2f(0, 0);
	//recoilType = 2;
	//crosshairType = Crosshairs::greenHalfCirc;
	//currentCrosshair = crosshairType;

	//crhRecoilActive = false;
	//crhRecoilSpeed = 50;
	//crhRecoilCalculated = false;
	//crhRecoilUp = false;

	//outOfControl = false;

	quickReloadActive = false;
	normalReloadClicked = false;
	quickReloadClicked = false;

	/*yPistolRecoilStrength = 5;
	yPistolRecoilStrengthTemp = yPistolRecoilStrength;
	yPistolRecoil = 0;
	pistolRecoilMultiplier = 1.8;
	pistolRecoilCoolDownTime = 0.3;*/

	//recoilCoolDown = pistolRecoilCoolDownTime;

	//pistolClipSize = 12;
	//pistolClip = pistolClipSize;

	quickReloadTime = 1.2;
	quickReloadTimer = quickReloadTime;

	normalReloadTime = 2.0;
	normalReloadTimer = normalReloadTime;

	gameTime = 0;
	gameOverTime = 0;

	//smgFireRate = 0.08;
	//smgFireRateTimer = smgFireRate;

	//targetRespawnTime = 0.4;
	//targetRespawn = targetRespawnTime;

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

//void Player::LoadCrosshair()
//{
//	if (currentCrosshair == Crosshairs::redCircleCross){ crosshairImage.loadFromFile("Assets/Images/Game/Crosshairs/crosshair_redCircleCross.png"); crosshairSprite.setScale(1, 1); }
//	else if (currentCrosshair == Crosshairs::greenHalfCirc){ crosshairImage.loadFromFile("Assets/Images/Game/Crosshairs/crosshair_greenHalfCirc.png"); crosshairSprite.setScale(1, 1); }
//	else if (currentCrosshair == Crosshairs::whiteHorizon){ crosshairImage.loadFromFile("Assets/Images/Game/Crosshairs/crosshair_whiteHorizon.png"); crosshairSprite.setScale(1, 1); }
//	else if (currentCrosshair == Crosshairs::redHorizon){ crosshairImage.loadFromFile("Assets/Images/Game/Crosshairs/crosshair_redHorizon.png"); crosshairSprite.setScale(1, 1); }
//	else if (currentCrosshair == Crosshairs::greenHorizon){ crosshairImage.loadFromFile("Assets/Images/Game/Crosshairs/crosshair_greenHorizon.png"); crosshairSprite.setScale(1, 1); }
//	else if (currentCrosshair == Crosshairs::clearDot){ crosshairImage.loadFromFile("Assets/Images/Game/Crosshairs/crosshair_clearDot.png"); crosshairSprite.setScale(1, 1); }
//	else if (currentCrosshair == Crosshairs::redDot){ crosshairImage.loadFromFile("Assets/Images/Game/Crosshairs/crosshair_redDot.png"); crosshairSprite.setScale(1, 1); }
//	else if (currentCrosshair == Crosshairs::pistol){ crosshairImage.loadFromFile("Assets/Images/Game/Crosshairs/crosshair_pistol.png"); crosshairSprite.setScale(4, 4); crosshairSprite.setOrigin(sf::Vector2f(75, 75)); }
//	else if (currentCrosshair == Crosshairs::smg){ crosshairImage.loadFromFile("Assets/Images/Game/Crosshairs/crosshair_smg.png"); crosshairSprite.setScale(4, 4); crosshairSprite.setOrigin(sf::Vector2f(75.5, 75)); }
//	else if (currentCrosshair == Crosshairs::predator){ crosshairImage.loadFromFile("Assets/Images/Game/Crosshairs/crosshair_predator.png"); crosshairSprite.setScale(1, 1); }
//}

//! Setup the player crosshair sprite
/*!
\Set the sprites origin to the centre of the sprite. Sets the texture for the sprite
\return none
\sa
*/
void Player::SetUp()
{
	//crosshairSprite.setOrigin(75, 75);
	//crosshairSprite.setTexture(crosshairImage, true);

	AddGun(Gun::PISTOL);
	currentGun = guns[Gun::PISTOL];

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

	//gameTimeText.setFont(font);
	//gameTimeText.setCharacterSize(50);
	//gameTimeText.setPosition(900, 635);
	//gameTimeText.setColor(sf::Color::Yellow);
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
	//for (int i = 0; i < pistolClip; i++)
	//{
	//	if (crhRecoilActive)
	//	{
	//		clipBulletSprite.setPosition(181 + i * 12, 650); //offset to less than the bullet width to create the illusion of the bullets moving up the clip
	//		window.draw(clipBulletSprite);
	//	}
	//	else
	//	{
	//		clipBulletSprite.setPosition(175 + i * 12, 650);
	//		window.draw(clipBulletSprite);
	//	}
	//}
	//window.draw(pistolClipSprite);
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
	//ss.str(std::string());
	//ss << pistolClip;
	//gunClipText.setString(ss.str());
	//if (pistolClip <= 3){ gunClipText.setColor(sf::Color::Red); }
	//else{ gunClipText.setColor(sf::Color::Yellow); }
	//if (pistolClip == 0){ gunClipText.setColor(sf::Color::Black); }
	//window.draw(gunClipText);

	//ss.str(std::string());
	//gameTime = roundf(gameTime * 100) / 100;
	//ss << gameTime;
	//gameTimeText.setString(ss.str());
	//window.draw(gameTimeText);

	//window.draw(crosshairSprite);

	currentGun->Draw(window);
}

//void Player::DrawResult(sf::RenderWindow& window)
//{
//	ss.str(std::string());
//	gameTime = roundf(gameTime * 100) / 100;
//	ss << gameTime;
//	string txt = "You shot 6 targets in: ";
//	gameTimeText.setString(txt + ss.str() + " seconds");
//	gameTimeText.setPosition(50, 600);
//
//	window.draw(gameTimeText);
//}

//! Update the Player
/*!
\Updates the player's crosshair position, creates a random X axis sway for the gun recoil(move to gun manager class later)
\Checks for a mouse click, allows the player to shoot and allows for the application of the recoil.
\return none
\sa
*/
void Player::Update(sf::RenderWindow& window, float frameTime)
{
	//gameTime += frameTime;
	//UpdateReloadTimes(frameTime);
	//smgFireRateTimer -= frameTime;

	//quickReloadClicked = false;

	//crosshairSprite.setPosition(sf::Mouse::getPosition(window).x + crhOffset.x, sf::Mouse::getPosition(window).y + crhOffset.y);

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
		if (currentGun->PISTOL == Gun::PISTOL)
		{
			leftMousePressed = true;
		}
	}

	currentGun->Update(window, frameTime);


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
	////cout << "Shot Fired" << endl;
	//if (pistolClip == 0 && CollisionManager::GetInstance()->CheckReloadCollision(crosshairSprite.getPosition(), reloadNormalSprite.getPosition(), reloadNormalSprite.getGlobalBounds()) == false){
	//	SoundManager::GetInstance()->PlayOutOfAmmo();
	//}
	//if (pistolClip > 0 && CollisionManager::GetInstance()->CheckReloadCollision(crosshairSprite.getPosition(), reloadNormalSprite.getPosition(), reloadNormalSprite.getGlobalBounds()) == false)
	//{
	//	pistolClip -= 1;
	//	SoundManager::GetInstance()->PlayPistolGunShot();
	//	if (recoilType == 1)
	//	{
	//		if (!CollisionManager::GetInstance()->CheckTargetCollision(sf::Vector2f(crosshairSprite.getPosition().x, crosshairSprite.getPosition().y)) == true)
	//		{
	//			BulletManager::GetInstance()->AddBullet(crosshairSprite.getPosition());
	//		}
	//			
	//	} //END Recoil Type 1
	//	if (recoilType == 2)
	//	{
	//		if (recoilCoolDown == pistolRecoilCoolDownTime)
	//		{
	//			if (!CollisionManager::GetInstance()->CheckTargetCollision(sf::Vector2f(crosshairSprite.getPosition().x, crosshairSprite.getPosition().y)) == true)
	//			{
	//				BulletManager::GetInstance()->AddBullet(crosshairSprite.getPosition());
	//			}
	//		}
	//		else if (recoilCoolDown < pistolRecoilCoolDownTime)
	//		{
	//			if (!CollisionManager::GetInstance()->CheckTargetCollision(sf::Vector2f(crosshairSprite.getPosition().x, crosshairSprite.getPosition().y) + PistolBulletRecoil()) == true)
	//			{
	//				BulletManager::GetInstance()->AddBullet(crosshairSprite.getPosition() + sf::Vector2f(randomXSway, yPistolRecoil));
	//				//CollisionManager::GetInstance()->SetBulletTargCollision(crosshairSprite.getPosition() + sf::Vector2f(randomXSway, yPistolRecoil));
	//			}
	//			cout << "yRecoil: " << yPistolRecoil << endl;
	//		}
	//		if (recoilTimerActive == true && recoilType == 2)
	//		{
	//			recoilCoolDown = pistolRecoilCoolDownTime;
	//		}
	//		recoilTimerActive = true;
	//	} //END Recoil Type 2
	//	crhRecoilActive = true;
	//}
}

//! Applys recoil to the crosshair sprite
/*!
\ Creates a recoil offset
\return none
\sa
*/
void Player::CrosshairRecoil(sf::RenderWindow& window, float frameTime)
{
	//if (crhRecoilCalculated == false)
	//{
	//	if (recoilType == 1)
	//	{
	//		//crhRecoilDirection = sf::Vector2f(getRandomSway().x, 5);
	//		crhRecoilDirection = sf::Vector2f(0, 5);
	//		Normalize(crhRecoilDirection); //Make recoilDirection a unit vector
	//		myOffset = crhRecoilDirection * crhRecoilSpeed * frameTime;
	//		crhRecoilCalculated = true;
	//	}
	//	if (recoilType == 2)
	//	{
	//		crhRecoilDirection = sf::Vector2f(0, 5);
	//		Normalize(crhRecoilDirection); //Make recoilDirection a unit vector
	//		myOffset = crhRecoilDirection * crhRecoilSpeed * frameTime;
	//		crhRecoilCalculated = true;
	//	}
	//}

	//if (recoilType == 1)
	//{
	//	if (getcrhRecoilDistance() < 10)
	//	{
	//		crhOffset.x += myOffset.x;
	//		crhOffset.y -= myOffset.y;
	//	}
	//	else
	//	{
	//		sf::Mouse::setPosition(sf::Vector2i(crosshairSprite.getPosition().x, crosshairSprite.getPosition().y), window);
	//		crhOffset = sf::Vector2f(0, 0);
	//		crhRecoilCalculated = false;
	//		crhRecoilActive = false;
	//	}
	//}
	//if (recoilType == 2)
	//{
	//	if (getcrhRecoilDistance() < 10 && crhRecoilUp == false)
	//	{
	//		//crhOffset -= myOffset;
	//		crhOffset.x += myOffset.x;
	//		crhOffset.y -= myOffset.y;
	//		if (getcrhRecoilDistance() > 10)
	//		{
	//			crhRecoilUp = true;
	//		}
	//	}
	//	if (crhRecoilUp == true)
	//	{
	//		crhOffset.x -= myOffset.x;
	//		crhOffset.y += myOffset.y;
	//	}
	//	if (crhRecoilUp == true && getcrhRecoilDistance() <= 1)
	//	{
	//		//crhOffset = sf::Vector2f(0, 0);
	//		crhRecoilUp = false;
	//		crhRecoilActive = false;
	//		crhRecoilCalculated = false;
	//	}
	//}
}

//sf::Vector2f Player::PistolBulletRecoil()
//{
//	sf::Vector2f rec;
//	if (outOfControl == false)
//	{
//		yPistolRecoilStrengthTemp *= pistolRecoilMultiplier;
//		rec = sf::Vector2f(getRandomSway().x, yPistolRecoil -= yPistolRecoilStrengthTemp);
//	}
//	if (yPistolRecoil < -100 && outOfControl == false)
//	{
//		outOfControl = true;
//	}
//	if (outOfControl == true)
//	{
//		randomXSway = rand() % 1000;
//		randomXSway = (randomXSway / 10) - 50;
//		float randomYSway = rand() % 1000;
//		randomYSway = (randomYSway / 50) - 10;
//		rec = sf::Vector2f(randomXSway, yPistolRecoil -= randomYSway);
//	}
//	return rec;
//}

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

