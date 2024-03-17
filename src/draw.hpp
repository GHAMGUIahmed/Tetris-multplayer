#pragma once 
#include<SFML/Graphics.hpp>
#include"RoundedRectangleShape.hpp"
#include"colors.hpp"
void drawText(sf::RenderWindow& wd, sf::String content, sf::Font font, int size, float x, float  y);
void drawRectangle(sf::RenderWindow& wd, float length, float width, float x, float y);