#pragma once 
#include<SFML/Graphics.hpp> 

/* on va d�finir les couleurs utilis�s dans le jeu  */
extern const sf::Color darkGrey;
extern const sf::Color green;
extern const sf::Color orange;
extern const sf::Color yellow;
extern const sf::Color purple;
extern const sf::Color cyan;
extern const sf::Color blue; 
extern const sf::Color lightBlue;
std::vector<sf::Color> GetCellColors();