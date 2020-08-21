#ifndef ALIMENTS_H_INCLUDED
#define ALIMENTS_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

class Aliments
{
    public :
    Aliments();
    Aliments(int x);
    ~Aliments();
    sf::Sprite getSpriteAliments() const;
    std::string getTexture() const;
    void deplacement();


    protected :
    sf::Texture m_aliments;
    std::string m_texture;
    sf::Sprite m_sprite_aliments;
    sf::Vector2u m_aliments_size;
    int m_depasseAlimentsX;
    int m_depasseAlimentsY;
};

#endif // ALIMENTS_H_INCLUDED
