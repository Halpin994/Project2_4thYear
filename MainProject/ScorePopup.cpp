#include "stdafx.h"
#include "ScorePopup.h"
#include "ScoreManager.h"
#include "Player.h"
#include "SFML/Graphics.hpp"
#include <SFML/OpenGL.hpp>



ScorePopup::ScorePopup(float points, sf::Vector2f pos, sf::Font& font, const char* colour)
{
	number = points;
	offset = sf::Vector2f(20, -50);

	position = pos + offset;

	timeToLive = 1.0f;
	stallTime = 0.5f;
	

	pointsText.setFont(font);
	pointsText.setCharacterSize(22);
	pointsText.setPosition(position);

	direction = sf::Vector2f((ScoreManager::GetInstance()->GetScorePos().x - 75) - pointsText.getPosition().x, ScoreManager::GetInstance()->GetScorePos().y - pointsText.getPosition().y);
	Normalize(direction);
	
	SetColour(colour);
}


ScorePopup::~ScorePopup()
{
}

void ScorePopup::Draw(sf::RenderWindow& window)
{
	ss.str(std::string());
	number = roundf(number * 1) / 1; //1000 means game time will be rounded to three decimal places
	ss << "+" << number;
	pointsText.setString(ss.str());
	window.draw(pointsText);
}

float ScorePopup::GetTimeToLive()
{
	return timeToLive;
}

void ScorePopup::Update(float ft, Player *player)
{
	stallTime -= ft;
	if (stallTime <= 0)
	{
		//pointsText.setPosition(player->getCurrentGun()->getGunPos() + offset);
		if (position.x < ScoreManager::GetInstance()->GetScorePos().x && position.y > ScoreManager::GetInstance()->GetScorePos().y)
		{
			timeToLive -= ft;
			position += direction * 2.0f * ft;
			pointsText.setPosition(position);
		}
		else
		{
			timeToLive -= ft;
		}
	}
}

//! Normalize a vector passed on call
/*!
\When this method is called a vector of type float must be passed. This method then normalises it (creates a unit vector)
\return Vector2f
\sa
*/
sf::Vector2f ScorePopup::Normalize(sf::Vector2f NormaliseMe)
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

float ScorePopup::GetStallTime()
{
	return stallTime;
}

void ScorePopup::AddScore(float points)
{
	if (stallTime <= 0.5)
	{
		stallTime = 0.5;
	}
	number += points;
}

void ScorePopup::SetColour(const char* colour)
{
	if (colour == "yellow")
	{
		pointsText.setColor(sf::Color::Yellow);
	}
	else if (colour == "red")
	{
		pointsText.setColor(sf::Color::Red);
	}
	else if (colour == "blue")
	{
		pointsText.setColor(sf::Color::Cyan);
	}
	else if (colour == "white")
	{
		pointsText.setColor(sf::Color::White);
	}
}
