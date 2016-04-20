#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

class Score
{
public:
	Score();
	~Score();

	float Score::GetScore();
	float Score::GetTime();
	float Score::GetAccuracy();
	void Score::SetScore(sf::String string, float myScore);
	void Score::SetTime(sf::String string, float myTime);

private:
	sf::String name;
	float score;
	float accuracy;
	float time;
};

