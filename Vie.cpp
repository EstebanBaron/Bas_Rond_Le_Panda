#include "Vie.h"

//Méthodes
Vie::Vie(int x)
{
    if(!m_vie.loadFromFile("vie.png"))
    {
        std::cout << "Erreur chargement vie" << std::endl;
    }

    m_vie_size = m_vie.getSize();
    m_sprite_vie.setTexture(m_vie);

    //position de la vie créée
    if (x==1)
        m_sprite_vie.setPosition(1,1);
    else if (x==2)
        m_sprite_vie.setPosition( m_vie_size.x ,1);
    else if (x == 3)
        m_sprite_vie.setPosition( 2*(m_vie_size.x ) ,1);
}

Vie::~Vie()
{

}

sf::Sprite Vie::getSpriteVie() const
{
    return m_sprite_vie;
}
