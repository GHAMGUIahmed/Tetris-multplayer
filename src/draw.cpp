#include"draw.hpp"
#include<iostream>
void drawText(sf::RenderWindow& wd, sf::String content, sf::Font font, int size, float x, float y)
{
	sf::Text text(content, font, size);
	text.setFillColor(sf::Color::White);
	text.setPosition(x, y);

	wd.draw(text);
}
void drawRectangle(sf::RenderWindow& wd, float length, float width, float x, float y)
{
	sf::RoundedRectangleShape rectangle(sf::Vector2f(length, width), 10, 10);
	rectangle.setPosition(x, y);
	rectangle.setFillColor(lightBlue);
	wd.draw(rectangle);

}