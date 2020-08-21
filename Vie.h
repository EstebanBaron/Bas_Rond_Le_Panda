#ifndef VIE_H_INCLUDED
#define VIE_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>

class Vie
{
    public :
    Vie(int x);
    ~Vie();
    sf::Sprite getSpriteVie() const;

    protected :
    sf::Texture m_vie;
    sf::Sprite m_sprite_vie;
    sf::Vector2u m_vie_size;
};

#endif // VIE_H_INCLUDED
