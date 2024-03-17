#include"colors.hpp"
const sf::Color darkGrey(26, 31, 40, 255);
//const sf::Color darkGrey = sf::Color::Cyan;
const sf::Color green = sf::Color::Green;
const sf::Color red = sf::Color::Red;
const sf::Color orange(226, 116, 17, 255);
const sf::Color yellow = sf::Color::Yellow;
const sf::Color purple(128, 0, 128, 255);
const sf::Color cyan = sf::Color::Cyan;
const  sf::Color blue = sf::Color::Blue;
const sf::Color lightBlue(59, 85, 162, 255);

std::vector<sf::Color> GetCellColors()
{
	return{ darkGrey,green,red,orange,yellow,purple,cyan,blue };
}