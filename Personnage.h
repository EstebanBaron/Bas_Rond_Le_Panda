#ifndef PERSONNAGE_H_INCLUDED
#define PERSONNAGE_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Aliments.h"
#include "Vie.h"
#include "Piece.h"

class Personnage
{
    public :
    Personnage();
    ~Personnage();
    void deplacement();
    sf::Sprite getSpritePerso() const;
    sf::Vector2u getSizePerso() const;
    int getDepasseBol() const;
    int getDepasseCoudes() const;

    protected :
    //attributs perso
    sf::Texture m_perso;
    sf::Sprite m_sprite_perso;
    sf::Vector2u m_perso_size;

    int m_depasseBol;
    int m_depasseCoudes;
};

#endif // PERSONNAGE_H_INCLUDED
