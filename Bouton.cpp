#include "Bouton.h"

//Méthodes
Bouton::Bouton()
{

}

Bouton::Bouton(int x, int y, std::string nom)
{
    if(!m_texture.loadFromFile(nom))
    {
        std::cout << "Erreur chargement bouton" << std::endl;
    }

    //Initialisations des attributs
    m_bouton_size = m_texture.getSize();

    m_spriteBouton.setTexture(m_texture);
    m_spriteBouton.setPosition(x,y);

}

Bouton::~Bouton()
{

}

sf::Sprite Bouton::getSpriteBouton() const
{
    return m_spriteBouton;
}
