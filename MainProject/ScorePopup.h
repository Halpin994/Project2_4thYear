#ifndef SCOREPOPUP
#define SCOREPOPUP

#include <sstream>
#include "SFML/Graphics.hpp"
#include <SFML/OpenGL.hpp>
#include "Player.h"

class ScorePopup
{
public:
	ScorePopup(float, sf::Vector2f, sf::Font& font, const char*);
	~ScorePopup();
	void Draw(sf::RenderWindow& window);
	float ScorePopup::GetTimeToLive();
	void ScorePopup::Update(float ft, Player *player);
	sf::Vector2f Normalize(sf::Vector2f);
	float ScorePopup::GetStallTime();
	void ScorePopup::AddScore(float points);
	void ScorePopup::SetColour(const char*);
private:
	
	sf::Text pointsText;
	std::stringstream ss;
	float number;
	float timeToLive;
	float stallTime;
	sf::Vector2f offset;
	sf::Vector2f direction;
	sf::Vector2f position;
};
#endif

