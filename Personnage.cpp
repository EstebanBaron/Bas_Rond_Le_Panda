#include "Personnage.h"

//variables
float speedPerso = 11;
float const largeurFenetre = 700;
float const longueurFenetre = 690;

//M�thodes
Personnage::Personnage()
{
    //Charger le personnage
    if(!m_perso.loadFromFile("images/panda.png"))
    {
        std::cout << "Erreur chargement perso" << std::endl;
    }
    m_perso.setSmooth(true);

    //initialisation des variables
    m_perso_size = m_perso.getSize();
    m_depasseBol = m_perso_size.y * 0.50;
    m_depasseCoudes = m_perso_size.x * 0.23;

    m_sprite_perso.setTexture(m_perso);
    m_sprite_perso.setPosition(((largeurFenetre/2.0)-(m_perso_size.x/2.0)),longueurFenetre-m_perso_size.y);
}

Personnage::~Personnage()
{

}

void Personnage::deplacement()
{

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        m_sprite_perso.move(-speedPerso,0);
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        m_sprite_perso.move(speedPerso,0);
    }

    if(m_sprite_perso.getPosition().x <= -m_depasseCoudes)
        m_sprite_perso.setPosition(sf::Vector2f(-m_depasseCoudes, m_sprite_perso.getPosition().y));

    if(m_sprite_perso.getPosition().x + m_perso_size.x >= largeurFenetre + m_depasseCoudes)
        m_sprite_perso.setPosition(sf::Vector2f(largeurFenetre - m_perso_size.x + m_depasseCoudes, m_sprite_perso.getPosition().y));
}

sf::Sprite Personnage::getSpritePerso() const
{
    return m_sprite_perso;
}

sf::Vector2u Personnage::getSizePerso() const
{
    return m_perso_size;
}

int Personnage::getDepasseBol() const
{
    return m_depasseBol;
}

int Personnage::getDepasseCoudes() const
{
    return m_depasseCoudes;
}

