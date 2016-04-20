#include "stdafx.h"
#include "Score.h"
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>


Score::Score()
{
	name = "";
	score = 0;
	accuracy = 0;
	time = 0;
}


Score::~Score()
{
}

void Score::SetScore(sf::String string, float myScore)
{
	name = string;
	score = myScore;
	//time = myTime;
	//accuracy = myAcc;
}

void Score::SetTime(sf::String string, float myTime)
{
	name = string;
	time = myTime;
}

float Score::GetTime()
{
	return time;
}

float Score::GetAccuracy()
{
	return accuracy;
}

float Score::GetScore()
{
	return score;
}
