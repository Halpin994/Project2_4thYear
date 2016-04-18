#ifndef SCOREMANAGER
#define SCOREMANAGER

#include <iostream>
#include <list>

#include "ScorePopup.h"

class ScoreManager
{
public:
	ScoreManager()
	{
		score = 0;
		font.loadFromFile("Assets/imagine_font.ttf");

		scoreText.setFont(font);
		scoreText.setCharacterSize(22);
		scoreText.setPosition(1000, 0);
		scoreText.setColor(sf::Color::Yellow);
		multiplier = 1.0f;
		topTarget_multiplier = 1.0f;
		bottomTarget_multiplier = 0.4f;
		base_multiplier = 0.2f;
	}
	~ScoreManager()
	{
		delete instance;
		instanceFlag = false;
		for (ScorePopup* s : scorePopUps)
		{
			delete s;
		}
	}
	static ScoreManager* GetInstance();

	void ScoreManager::AddScore(float, sf::Vector2f&, const char*, const char*);
	void ScoreManager::SetScore(float);
	float ScoreManager::GetScore();

	void ScoreManager::Draw(sf::RenderWindow& window);

	void ScoreManager::Update(float ft, Player *player);
	sf::Vector2f ScoreManager::GetScorePos();

private:

	static bool instanceFlag;
	static ScoreManager* instance;

	float score;
	float prevPoints;

	float multiplier;
	float topTarget_multiplier;
	float bottomTarget_multiplier;
	float base_multiplier;

	string prevTargHit;

	std::list<ScorePopup*> scorePopUps;

	sf::Font font;

	sf::Text scoreText;
	std::stringstream ss;

};
#endif 
