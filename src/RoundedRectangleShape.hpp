#pragma once

#include <SFML/Graphics/Shape.hpp>
//une classe personnalisée , qui hérite de la class sf::Shape pour créer des rectangles arrondis avec SFML.
namespace sf
{

    class RoundedRectangleShape : public sf::Shape
    {
    public:

        explicit RoundedRectangleShape(const Vector2f& size = Vector2f(0, 0), float radius = 0, unsigned int cornerPointCount = 0); 
        // Constructeur de la classe RoundedRectangleShape

        void setSize(const Vector2f& size);
        // Méthode pour définir la taille du RoundedRectangleShape


        const Vector2f& getSize() const;
        // Méthode pour obtenir la taille actuelle du RoundedRectangleShape


        void setCornersRadius(float radius);
        // Méthode pour définir le rayon des coins du RoundedRectangleShape

        float getCornersRadius() const;
        // Méthode pour obtenir le rayon des coins du RoundedRectangleShape


        void setCornerPointCount(unsigned int count);
        // Méthode pour définir le nombre de points par coin du RoundedRectangleShape


        virtual std::size_t getPointCount() const;
        // Méthode virtuelle pour obtenir le nombre total de points du RoundedRectangleShape


        virtual sf::Vector2f getPoint(std::size_t index) const;
        // Méthode virtuelle pour obtenir un point spécifique du RoundedRectangleShape à l'index donné

    private:

        Vector2f mySize;  // Taille du RoundedRectangleShape

        float myRadius;  // rayon des coins du RoundedRectangleShape
        unsigned int myCornerPointCount;  // Nombre de points par coin du RoundedRectangleShape

    };
}
 
