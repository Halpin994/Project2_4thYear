#include "stdafx.h"

#include "SFML/Graphics.hpp"
#include <SFML/OpenGL.hpp>

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "ScoreManager.h"
#include "Player.h"
#include <algorithm>

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

void ScoreManager::AddScore(float points, sf::Vector2f &pos, const char* colour, const char* targetHit)
{
	if (scorePopUps.size() == 0)
	{
		ScorePopup* s = new ScorePopup(points, pos, font, colour);
		scorePopUps.push_back(s);
		prevPoints = points;
		score += points;
		multiplier = 1.0f;
	}
	else
	{
		std::list<ScorePopup*>::iterator popUpIter = scorePopUps.begin();

		if ((*popUpIter)->GetStallTime() > 0 && prevPoints == points)
		{
			if (targetHit == "top"){multiplier += topTarget_multiplier;}
			else if (targetHit == "bottom"){ multiplier += bottomTarget_multiplier; }
			(*popUpIter)->AddScore(points * multiplier);
			(*popUpIter)->SetColour(colour);
			score += points * multiplier;
		}
		else if ((*popUpIter)->GetStallTime() > 0)
		{
			multiplier += base_multiplier;
			(*popUpIter)->AddScore(points * multiplier);
			(*popUpIter)->SetColour(colour);
			score += points * multiplier;
		}
		else //((*popUpIter)->GetStallTime() < 0)
		{
			ScorePopup* s = new ScorePopup(points, pos, font, colour);
			scorePopUps.push_front(s);
			score += points;
			multiplier = 1.0f;
		}
	}
	prevPoints = points;
	prevTargHit = targetHit;
	
}

void ScoreManager::SetScore(float s)
{
	score = s;
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

void ScoreManager::LoadHighScoreTable(sf::String string)
{
	if (string == "Level1-Highscore")
	{
		ClearScoreTable(highscores);
		std::string line;
		readFile.open("Assets/Highscores/Level1-Highscore.txt");

		int i = 0;
		while (getline(readFile, line) && i < 10)
		{
			float score = stof(line);

			AddToHighScores(score, false);

			i++;
		}
		readFile.close();
	}
	else if (string == "Level1-Highspeed")
	{
		ClearScoreTable(hightimes);
		std::string line;
		readFile.open("Assets/Highscores/Level1-Highspeed.txt");

		int i = 0;
		while (getline(readFile, line) && i < 10)
		{
			float time = stof(line);

			AddToFastestTimes(time, false);

			i++;
		}
		readFile.close();
	}
	else if (string == "Level1-Headshots")
	{
		ClearScoreTable(headshotScores);
		std::string line;
		readFile.open("Assets/Highscores/Level1-Headshots.txt");

		int i = 0;
		while (getline(readFile, line) && i < 10)
		{
			float score = stof(line);

			AddToHeadshotScores(score, false);

			i++;
		}
		readFile.close();
	}
}

void ScoreManager::SaveHighScoreTable(sf::String string)
{
	if (string == "Level1-Highscore")
	{
		writeFile.open("Assets/Highscores/Level1-Highscore.txt", std::ofstream::out | std::ofstream::trunc);
		writeFile.close();
		writeFile.open("Assets/Highscores/Level1-Highscore.txt");
		for (int i = 0; i < highscores.size(); i++)
		{
			writeFile << highscores[i]->GetScore() <<  endl;
		}
	}
	else if (string == "Level1-Highspeed")
	{
		writeFile.open("Assets/Highscores/Level1-Highspeed.txt", std::ofstream::out | std::ofstream::trunc);
		writeFile.close();
		writeFile.open("Assets/Highscores/Level1-Highspeed.txt");
		for (int i = 0; i < hightimes.size(); i++)
		{
			writeFile << hightimes[i]->GetTime() << endl;
		}
	}
	else if (string == "Level1-Headshots")
	{
		writeFile.open("Assets/Highscores/Level1-Headshots.txt", std::ofstream::out | std::ofstream::trunc);
		writeFile.close();
		writeFile.open("Assets/Highscores/Level1-Headshots.txt");
		for (int i = 0; i < headshotScores.size(); i++)
		{
			writeFile << headshotScores[i]->GetScore() << endl;
		}
	}

	for (ScorePopup* s : scorePopUps)
	{
		delete s;
	}
	scorePopUps.clear();
}

void ScoreManager::AddToHighScores(float score, bool sort)
{
	Score* myScore = new Score;
	myScore->SetScore("Conor", score);
	highscores.push_back(myScore);

	if (sort == true)
	{
		std::cout << "\n\nPRE" << std::endl;
		for (std::vector<Score*>::iterator iter = highscores.begin(), end = highscores.end(); iter != end; iter++)
		{
			std::cout << (*iter)->GetScore() << std::endl;
		}

		SortScores(highscores);

		if (highscores.size() > 10)
		{
			for (int i = 0; i < highscores.size() - 10; i++)
			{
				highscores.pop_back();
			}
		}

		std::cout << "\n\nPOST" << std::endl;
		for (std::vector<Score*>::iterator iter = highscores.begin(), end = highscores.end(); iter != end; iter++)
		{
			std::cout << (*iter)->GetScore() << std::endl;
		}

	}
}

void ScoreManager::AddToHeadshotScores(float score, bool sort)
{
	Score* myScore = new Score;
	myScore->SetScore("Conor", score);
	headshotScores.push_back(myScore);

	if (sort == true)
	{
		std::cout << "\n\nPRE" << std::endl;
		for (std::vector<Score*>::iterator iter = headshotScores.begin(), end = headshotScores.end(); iter != end; iter++)
		{
			std::cout << (*iter)->GetScore() << std::endl;
		}

		SortScores(headshotScores);

		if (highscores.size() > 10)
		{
			for (int i = 0; i < headshotScores.size() - 10; i++)
			{
				headshotScores.pop_back();
			}
		}

		std::cout << "\n\nPOST" << std::endl;
		for (std::vector<Score*>::iterator iter = headshotScores.begin(), end = headshotScores.end(); iter != end; iter++)
		{
			std::cout << (*iter)->GetScore() << std::endl;
		}

	}
}

void ScoreManager::AddToFastestTimes(float time, bool sort)
{
	Score* myTime = new Score;
	myTime->SetTime("Conor", time);
	hightimes.push_back(myTime);

	if (sort == true)
	{
		SortTimes();

		if (hightimes.size() > 10)
		{
			for (int i = 0; i < hightimes.size() - 10; i++)
			{
				hightimes.pop_back();
			}
		}
	}
}

void ScoreManager::ClearScoreTable(vector<Score*>& scores)
{
	if (scores.empty()) return;

	for (std::vector<Score*>::iterator iter = scores.begin(), end = scores.end(); iter != end; iter++)
	{
		delete (*iter);
	}
	scores.clear();
	scores.reserve(10);
}

void ScoreManager::SortScores(vector<Score*>& scores)
{
	Score* largest;
	for (std::vector<Score*>::iterator a = scores.begin(), e = --scores.end(); a != e; ++a)
	{
		largest = *a;

		std::vector<Score*>::iterator b = a;
		for (std::vector<Score*>::iterator e = scores.end(); b != e;)
		{
			if (++b == e)
			{
				--b;
				break;
			}

			if ((*b)->GetScore() > largest->GetScore())
			{
				largest = *b;
			}
		}

		if (largest != *a)
		{
			Score* temp = *a;
			*a = largest;
			*b = temp;
		}
	}
}

void ScoreManager::SortTimes()
{
	Score* largest;
	for (std::vector<Score*>::iterator a = hightimes.begin(), e = --hightimes.end(); a != e; ++a)
	{
		largest = *a;

		std::vector<Score*>::iterator b = a;
		for (std::vector<Score*>::iterator e = hightimes.end(); b != e;)
		{
			if (++b == e)
			{
				--b;
				break;
			}

			if ((*b)->GetTime() < largest->GetTime())
			{
				largest = *b;
			}
		}

		if (largest != *a)
		{
			Score* temp = *a;
			*a = largest;
			*b = temp;
		}
	}
}

vector<Score*> ScoreManager::GetHighScores()
{
	return highscores;
}

vector<Score*> ScoreManager::GetHighTimes()
{
	return hightimes;
}

vector<Score*> ScoreManager::GetHeadshotScores()
{
	return headshotScores;
}