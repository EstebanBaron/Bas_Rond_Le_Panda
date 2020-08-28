#include "Aliments.h"

const float Aliments::m_speedAliments = 10.0;

//Methodes
Aliments::Aliments() {
    m_aliments = sf::Texture();
    m_texture = "";
    m_sprite_aliments = sf::Sprite();
    m_aliments_size = sf::Vector2u();
    m_depasseAlimentsX = -1;
    m_depasseAlimentsY = -1; 
    m_zone = -1;
    m_numAlim = -1;
}

Aliments::Aliments(int zone) {
    // srand(time(NULL));

    //Variables
    int unQuartEcran = (700.0/4);
    int moitierEcran = (700.0/2);
    int troisQuartEcran = 3 * (700.0/4);

    int tailleAliment = 111;
    int rangeX = 62;
    
    int positionX = 0;
    int positionY = -112;

    m_zone = zone;
    if (m_zone == 0)
        positionX = rand() % (unQuartEcran - tailleAliment);
    else if (m_zone == 1)
        positionX = rand() % rangeX + unQuartEcran;
    else if (m_zone == 2)
        positionX = rand() % rangeX + moitierEcran;
    else
        positionX = rand() % rangeX + troisQuartEcran;

    m_numAlim = rand() % 4;
    if (m_numAlim == 0)
        m_texture = "images/poisson_pourri.png";
    if (m_numAlim == 1)
        m_texture = "images/sushis.png";
    else if (m_numAlim == 2)
        m_texture = "images/raviolis.png";
    else if(m_numAlim == 3)
        m_texture = "images/soupe.png";

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

Aliments::~Aliments() {
}

sf::Sprite Aliments::getSpriteAliments() const
{
    return m_sprite_aliments;
}

std::string Aliments::getTexture() const
{
    return m_texture;
}

int Aliments::getZone() const {
    return m_zone;
}

void Aliments::deplacement()
{
    m_sprite_aliments.move(0, m_speedAliments);
}
