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
		scoreText.setPosition(1050, 100);
		scoreText.setColor(sf::Color::Yellow);
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

	void ScoreManager::AddScore(float, sf::Vector2f&, const char*);
	void ScoreManager::SetScore(float);
	float ScoreManager::GetScore();

	void ScoreManager::Draw(sf::RenderWindow& window);

	void ScoreManager::Update(float ft, Player *player);
	sf::Vector2f ScoreManager::GetScorePos();

private:

	static bool instanceFlag;
	static ScoreManager* instance;

	float score;
	std::list<ScorePopup*> scorePopUps;

	sf::Font font;

	sf::Text scoreText;
	std::stringstream ss;

};
#endif 
