#include"colors.hpp"
#include"Tetris.hpp"
#include"RoundedRectangleShape.hpp" 

void Tetris::drawText(sf::String content, int size, float x, float y, bool Gras = false)
{
// à utiliser pour l'affichage des différents textes
    sf::Text text(content, font, size);
    text.setFillColor(sf::Color::White);
    text.setPosition(x, y);
    if (Gras) text.setStyle(sf::Text::Bold);
    render.draw(text);


}
void Tetris::drawRectangle(float length, float width, float x, float y)
// à utiliser pour l'affichage des différents rectangles 

{
    sf::RoundedRectangleShape rectangle(sf::Vector2f(length, width), 10, 10);
    rectangle.setPosition(x, y);
    rectangle.setFillColor(lightBlue);
    render.draw(rectangle);
}



// dans le mode offline 
void Tetris::draw()
{
    // dessiner le jeu 

    render.clear();

    sf::Texture BackgroundTexture;
    if (!BackgroundTexture.loadFromFile("assets/OIP.jpg")) std::cout << "no image " << std::endl;



// background du jeu 
    sf::Sprite background;
    sf::Vector2u TextureSize;  //Added to store texture size.
    sf::Vector2u WindowSize;   //Added to store window size.
    TextureSize = BackgroundTexture.getSize();//Get size of texture.
    sf::Vector2u renderSize = render.getSize();
    float ScaleX = (float)renderSize.x / TextureSize.x;
    float ScaleY = (float)renderSize.y / TextureSize.y;     
    background.setTexture(BackgroundTexture);
    background.setScale(ScaleX, ScaleY);        
    background.setColor(sf::Color(255, 255, 255, 150));
    render.draw(background);

    drawRectangle(300, 100, 550, 70); // rectangle du score.
    drawRectangle(250, 180, 550, 300); // rectangle du bloc suivant.
    drawRectangle(300, 100, 550, 600);//rectangle du niveau
    drawText("Score", 40, 650, 5); 
    drawText("Next", 40, 640, 250);


    sf::Text scrtxt(std::to_string(score), font, 70);//convertir le score en objet sf::text
    int scoresize = scrtxt.getGlobalBounds().width; //largeur du score , à utiliser pour centrer le score dans son rectangle. 
    drawText(std::to_string(score), 70, 550 + (300 - scoresize) / 2, 75, true);//affichage du score
    drawText("Level", 40, 650, 550);
    drawText(std::to_string(level), 70, 680, 610, true);// affichage du niveau 

    if (gameOver)
    {
        drawText("Game Over ", 40, 600, 750); // affichage du text gameover en cas de perte . 
        if (client != NULL) client->sendGameOver();

    }
    grid.draw(render, currentBlock.get_cell_postion());
    currentBlock.draw(render, 11, 11, Animated, clockAnimated);
    nextBlock.draw(render, nextBlock.next_x_offset, nextBlock.next_y_offset, false, clockAnimated);

    render.display();

}
 

// pour le mode online différencier entre les grids 

void Tetris::drawUserWorlds()
{
    int cell_size = 35;
    int mini_cell_size = 20;
    int border = 15;
    int starty = 52;
    int startx = cell_size * 10 + 100;
    std::vector<sf::Color> colors = GetCellColors();


    int step = 0;
    int usr = -1;

    for (int n = 0; n < 2; n++) {

        int posy = step * mini_cell_size * 22 + step * 66;

        usr++;
        if (client->getId() == usr) {
            usr++;
        }



        step++;
        int** world = client->getUserWorld(usr);

        int k = 0;

        world[0][0] = 0;
        for (int i = 0; i < 22; ++i) {
            int temp = world[i][0];
            for (int j = 0; j < 9; ++j) {
                world[i][j] = world[i][j + 1];
            }
            world[i][9] = temp;
        }

        drawText(client->getName(usr), 40, 500, posy, false);
        for (int x = 0; x < 22; x++) {
            for (int y = 0; y < 10; y++) {
                sf::RectangleShape rectangle1;
                int cell_value = world[x][y];

                sf::RectangleShape rectangle;
                rectangle1.setSize(sf::Vector2f(mini_cell_size - 1, mini_cell_size - 1));
                rectangle1.setPosition(y * mini_cell_size + 1000, posy + x * mini_cell_size + 50);
                rectangle1.setOutlineThickness(1);
                rectangle1.setOutlineColor(sf::Color::Cyan);

                rectangle1.setFillColor(colors[cell_value]);

                render.draw(rectangle1);
            }


        }

        drawText(client->getName(usr), 40, 500, posy, false);
        int pieceID = client->getPieceID(usr);
        int* piece = client->getPiece(usr);

        for (int p = 0; p < 8; p += 2) {
            
            sf::RectangleShape rectangle;
            rectangle.setSize(sf::Vector2f(mini_cell_size - 1, mini_cell_size - 1));
            rectangle.setPosition(piece[p + 1] * mini_cell_size + 1000, posy + piece[p] * mini_cell_size + 50);

            rectangle.setFillColor(colors[pieceID]);

            render.draw(rectangle);
        }

    }
    usr++;
    int** world = client->getUserWorld(usr);
    int posy = 300;
    int posx = 1000 + 22 * mini_cell_size;
    int k = 0;

    world[0][0] = 0;
    for (int i = 0; i < 22; ++i) {
        int temp = world[i][0];
        for (int j = 0; j < 9; ++j) {
            world[i][j] = world[i][j + 1];
        }
        world[i][9] = temp;
    }
    drawText(client->getName(usr), 40, posx, posy, false);
    for (int x = 0; x < 22; x++) {
        for (int y = 0; y < 10; y++) {
            sf::RectangleShape rectangle1;
            int cell_value = world[x][y];

            sf::RectangleShape rectangle;
            rectangle1.setSize(sf::Vector2f(mini_cell_size - 1, mini_cell_size - 1));
            rectangle1.setPosition(y * mini_cell_size + posx, posy + x * mini_cell_size + 11);
            rectangle1.setOutlineThickness(1);
            rectangle1.setOutlineColor(sf::Color::Cyan);

            rectangle1.setFillColor(colors[cell_value]);

            render.draw(rectangle1);
        }


    }

    int pieceID = client->getPieceID(usr);
    int* piece = client->getPiece(usr);

    for (int p = 0; p < 8; p += 2) {

        
        sf::RectangleShape rectangle;
        rectangle.setSize(sf::Vector2f(mini_cell_size - 1, mini_cell_size - 1));
        rectangle.setPosition(piece[p + 1] * mini_cell_size + posx, posy + piece[p] * mini_cell_size + 11);

        rectangle.setFillColor(colors[pieceID]);

        render.draw(rectangle);
    }

    render.display();
}
