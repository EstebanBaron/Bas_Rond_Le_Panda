#ifndef BOUTON_H_INCLUDED
#define BOUTON_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

class Bouton
{
    public :
    Bouton();
    Bouton(int x, int y, std::string nom);
    ~Bouton();
    sf::Sprite getSpriteBouton() const;

    protected :
    sf::Sprite m_spriteBouton;
    sf::Texture m_texture;
    sf::Vector2u m_bouton_size;
};

#endif // BOUTON_H_INCLUDED
