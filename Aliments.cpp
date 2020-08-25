#include "Aliments.h"

//Methodes
Aliments::~Aliments() {
}

Aliments::Aliments(int zone) {
    srand(time(NULL));

    //Variables
    float speedAliments = 6;
    int TailleFenetreMoinsTailleAliment = 589;

    int unQuartEcran = (700.0/4);
    int moitierEcran = (700.0/2);
    int troisQuartEcran = 3 * (700.0/4);

    int tailleAliment = 111;
    int rangeX = 62;
    
    int positionX = 0;
    int positionY = -112;

    m_zone = zone;
    switch (m_zone)
    {
        case m_zone == 0 :
            positionX = rand() % (unQuartEcran - tailleAliment);
            break;
        case m_zone == 1 :
            positionX = rand() % rangeX + unQuartEcran;
        case m_zone == 2 :
            positionX = rand() % rangeX + moitierEcran;
        case m_zone == 3 :
            positionX = rand() % rangeX + troisQuartEcran;
        default:
            positionX = rand() % rangeX + unQuartEcran;
            break;
    }

    m_numAlim = rand() % 4;
    switch (m_numAlim)
    {
        case m_numAlim == 0:
            m_texture = "images/poisson_pourri.png";
            break;
        case m_numAlim == 1:
            m_texture = "images/sushis.png";
            break;
        case m_numAlim == 2:
            m_texture = "images/raviolis.png";
            break;
        case m_numAlim == 3:
            m_texture = "images/soupe.png";
            break;
        default:
            m_texture = "images/poisson_pourri.png";
            break;
    }

    if(!m_aliments.loadFromFile(m_texture)) {
        std::cout << "Erreur chargement aliment" << std::endl;
    }
    m_sprite_aliments.setPosition(positionX, positionY);
    m_aliments.setSmooth(true);

    //Initialisations des attributs
    m_aliments_size = m_aliments.getSize();
    m_depasseAlimentsX = m_aliments_size.x - 30;
    m_depasseAlimentsY = m_aliments_size.y - 50;

    m_sprite_aliments.setTexture(m_aliments);

}

sf::Sprite Aliments::getSpriteAliments() const
{
    return m_sprite_aliments;
}

std::string Aliments::getTexture() const
{
    return m_texture;
}

void Aliments::deplacement()
{
    m_sprite_aliments.move(0,speedAliments);
}
