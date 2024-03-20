#pragma once
#include<vector>
#include<map>
#include"position.hpp"
#include"colors.hpp"
class Block

{
public : 
	int id;
	std::map < int, std::map<int, std::vector<Position>> > cells; 
	// pour représenter tous les positions possible que le bloc peut prendre 
	int rotationState;   // représente la rotation dde bloc, elle est le  premier int de cells 
	
	int pivot;
	/* Le deuxième entier dans la structure cells joue le rôle de  la manipulation des rotations de blocs
	dans notre programme. Chaque état de rotation possède un pivot spécifiquement défini, qui se révèle essentiel lors 
	des rotations vers la droite ou la gauche. En fonction de la position actuelle du bloc, nous déterminons ce pivot.
	==>Sa fonction principale est de permettre la rotation fluide du bloc, quel que soit le cas rencontré,
	en garantissant que le bloc puisse tourner dans toutes les configurations possibles de manière appropriée.*/

	int next_x_offset; // offset vertical du bloc lorsque affiché dans next bloc
	int next_y_offset; // offset vertical du bloc lorsque affiché dans next bloc

	Block();
	void draw(sf::RenderTexture& texture , int offsetx, int offsety,bool Stop,sf::Clock& clock);
	// cette fonction pour une raison d'animation quand on fige le block
	void drawtra(sf::RenderTexture& texture, int offsetx, int offsety);
	void move(int rows, int cols);
	std::vector<Position> get_cell_postion(); // retourne les positions courantes du bloc 
	void Rotate(int i );
	int getLastRow();
	void initialiserPivot(); // pour changer la valeur de pivot selon sa pos dans le Grid 

protected: 
	int cell_size;
	std::vector<sf::Color>	colors;  

	int rowOffset;  /*la position de l'origine de bloc */
	int colOffset; 
	
};  

int min_col(std::vector<Position> curentCell); 
int max_col(std::vector<Position> curentCell);
int min_row(std::vector<Position> currentCell);
