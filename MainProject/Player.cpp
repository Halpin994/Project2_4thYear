#include "stdafx.h"
#include "SFML/Graphics.hpp"
#include <SFML/OpenGL.hpp>

#include <iostream>
#include "Math.h"
#include "Player.h"
#include "BulletManager.h"
#include "Target.h"

Target target;

Player::Player()
{
	mousePressed = true;
	recoilActive = false;
	recoilDirection = sf::Vector2f(0, 5 / sqrt(26));
	recoilSpeed = 0;
	recoilTime = 0;
	offset = sf::Vector2f(0, 0);

	Load();
	SetUp();
}

Player::~Player()
{

}

void Player::Init(sf::RenderWindow& window)
{
	crosshairSprite.setPosition(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
}

void Player::Load()
{
	crosshairImage.loadFromFile("crosshair.png");
}

void Player::SetUp()
{
	crosshairSprite.setOrigin(75, 75);
	crosshairSprite.setTexture(crosshairImage, true);
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(crosshairSprite);
}

void Player::Update(sf::RenderWindow& window, float frameTime)
{
	float randomXSway = rand() % 1000;
	randomXSway = (randomXSway / 200) - 2.5;
	//cout << randomXSway << endl;
	recoilDirection = sf::Vector2f(randomXSway / sqrt(26), 5 / sqrt(26));

	if (sf::Mouse::getPosition(window).x > 175 && sf::Mouse::getPosition(window).x < 1030 && sf::Mouse::getPosition(window).y < 590)
	{
		crosshairSprite.setPosition(sf::Mouse::getPosition(window).x + offset.x, sf::Mouse::getPosition(window).y + offset.y);
	}

	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		mousePressed = false;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))// && mousePressed == false)
	{
		mousePressed = true;
		Shoot(window);
	}
	if (recoilActive)
	{
		Recoil(window, frameTime);
	}
}

void Player::Shoot(sf::RenderWindow& window)
{
	cout << "Shot Fired" << endl;
	recoilActive = true;
	if (crosshairSprite.getPosition().x > target.GetPosition().x && crosshairSprite.getPosition().x < target.GetPosition().x + target.GetWidth()
		&& crosshairSprite.getPosition().y > target.GetPosition().y + 10 && crosshairSprite.getPosition().y < target.GetPosition().y + target.GetHeight())
	{
		BulletManager::GetInstance()->AddBullets(2, crosshairSprite.getPosition());
	}
	else
	BulletManager::GetInstance()->AddBullets(1, crosshairSprite.getPosition());
}

void Player::Recoil(sf::RenderWindow& window, float frameTime)
{
	sf::Vector2f myOffset = recoilDirection * recoilSpeed * frameTime;

	//recoilTime += frameTime;
	//if (recoilTime < 0.06)
	if (offset.y > -20)
	{
		offset.x += myOffset.x;
		offset.y -= myOffset.y;
		//cout << "After offset: " << offset.y << endl;
	}
	else
	{
		sf::Mouse::setPosition(sf::Vector2i(crosshairSprite.getPosition().x, crosshairSprite.getPosition().y), window);
		offset = sf::Vector2f(0, 0);
		recoilActive = false;
		recoilTime = 0;
	}
}

sf::Vector2f Player::Normalize(sf::Vector2i NormaliseMe)
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

float Player::getVectorLength(sf::Vector2i vec)
{
	return sqrtf(powf(vec.x, 2) + powf(vec.y, 2));
}