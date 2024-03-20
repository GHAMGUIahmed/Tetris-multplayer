#pragma once

#include <SFML/Graphics/Shape.hpp>
//une classe personnalisée , qui hérite de la class sf::Shape pour créer des rectangles arrondis avec SFML.
namespace sf
{

    class RoundedRectangleShape : public sf::Shape
    {
    public:

        explicit RoundedRectangleShape(const Vector2f& size = Vector2f(0, 0), float radius = 0, unsigned int cornerPointCount = 0); 

        void setSize(const Vector2f& size);


        const Vector2f& getSize() const;


        void setCornersRadius(float radius);
        // Méthode pour définir le rayon des coins du RoundedRectangleShape

        float getCornersRadius() const;


        void setCornerPointCount(unsigned int count);
        // Méthode pour définir le nombre de points par coin du RoundedRectangleShape


        virtual std::size_t getPointCount() const;
        // Méthode virtuelle pour obtenir le nombre total de points du RoundedRectangleShape


        virtual sf::Vector2f getPoint(std::size_t index) const;
        // Méthode virtuelle pour obtenir un point spécifique du RoundedRectangleShape à l'index donné

    private:

        Vector2f mySize;  

        float myRadius;  
        unsigned int myCornerPointCount;  

    };
}
 
