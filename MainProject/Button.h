#ifndef BUTTON
#define BUTTON
#include "SFML/Graphics.hpp"
class Button
{
public:
	~Button();
	Button::Button(sf::Vector2f& pos, sf::String& string, int& characterSize, sf::Font& font);
	void Button::Update(sf::Vector2f& crosshairPos);
	void Button::Draw(sf::RenderWindow& window);
private:
	sf::Vector2f position;
	sf::Text buttonText;
};
#endif 

