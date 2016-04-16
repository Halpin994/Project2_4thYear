#ifndef BUTTON
#define BUTTON
#include "SFML/Graphics.hpp"
#include <SFML/OpenGL.hpp>

//typedef  void (Menu::*MenuMemFunc)();
class Menu;
class Button
{
public:
	~Button();
	Button(sf::Vector2f pos, sf::String string, int characterSize, sf::Font& font, void (Menu::*MenuMemFunc)());
	void Button::Update(sf::Vector2f crosshairPos, Menu* menu);
	void Button::Draw(sf::RenderWindow& window);
	sf::FloatRect Button::GetBounds();
	sf::Vector2f Button::GetPosition();
private:
	sf::Vector2f position;
	sf::Text buttonText;
	bool highlighted;
	bool clicked;
	void (Menu::*btn_Func)();
};
#endif 

