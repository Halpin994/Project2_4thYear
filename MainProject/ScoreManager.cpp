#include "stdafx.h"

#include "SFML/Graphics.hpp"
#include <SFML/OpenGL.hpp>

#include <iostream>
#include "ScoreManager.h"
#include "Player.h"

bool ScoreManager::instanceFlag = false;
ScoreManager* ScoreManager::instance = NULL;

//! (Brief desc)
/*!
\(Detailed desc)
\return
\sa
*/
ScoreManager* ScoreManager::GetInstance()
{
	if (!instanceFlag)
	{
		instance = new ScoreManager;
		instanceFlag = true;
		return instance;
	}
	else
	{
		return instance;
	}
}

void ScoreManager::AddScore(float points, sf::Vector2f &pos, const char* colour)
{
	if (scorePopUps.size() == 0)
	{
		ScorePopup* s = new ScorePopup(points, pos, font, colour);
		scorePopUps.push_back(s);
	}
	else
	{
		std::list<ScorePopup*>::iterator popUpIter = scorePopUps.begin();

		if ((*popUpIter)->GetStallTime() < 0)
		{
			ScorePopup* s = new ScorePopup(points, pos, font, colour);
			scorePopUps.push_front(s);
		}
		else if ((*popUpIter)->GetStallTime() > 0)
		{
			(*popUpIter)->AddScore(points);
			(*popUpIter)->SetColour(colour);
		}
	}
	score += points;
}

void ScoreManager::SetScore(float f)
{
	score = f;
}

float ScoreManager::GetScore()
{
	return score;
}

sf::Vector2f ScoreManager::GetScorePos()
{
	return scoreText.getPosition();
}

void ScoreManager::Update(float ft, Player *player)
{
	for (std::list<ScorePopup*>::iterator popUpIter = scorePopUps.begin(), endIter = scorePopUps.end(); popUpIter != endIter;)
	{
		//Pull the pointer from the iterator
		//Target* currentTarget = (*targetIter);

		//If we have a TTL, update
		if ((*popUpIter)->GetTimeToLive() > 0)
		{
			(*popUpIter)->Update(ft, player);

			//And then update the iterator here
			popUpIter++;
		}
		else
		{
			//Delete target
			delete (*popUpIter);

			//Update iterator by erasing
			popUpIter = scorePopUps.erase(popUpIter);
		}
	}
}

void ScoreManager::Draw(sf::RenderWindow& window)
{
	ss.str(std::string());
	score = roundf(score * 1) / 1; //1000 means game time will be rounded to three decimal places
	ss << "Score: " << score;
	scoreText.setString(ss.str());
	window.draw(scoreText);

	for (ScorePopup* s : scorePopUps)
	{
		s->Draw(window);
	}
}