#include "Aliments.h"


//Variables
float speedAliments = 6;
int TailleFenetreMoinsTailleAliment = 589;
int unQuartEcran = (700.0/4);
int moitierEcran = (700.0/2);
int troisQuartEcran = 3 * (700.0/4);
int TailleAliment = 111;
int range = 201;
int rangeX456 = 62;

//Methodes

Aliments::Aliments(int x)
{
    srand(time(NULL));

    if(x == 1)
    {
        m_texture = "poisson_pourri.png";
        if(!m_aliments.loadFromFile(m_texture))
        {
            std::cout << "Erreur chargement aliment" << std::endl;
        }
        m_sprite_aliments.setPosition(rand() % (unQuartEcran - TailleAliment), rand() % range - 300);
    }
    else if(x == 2)
    {
        m_texture = "raviolis.png";
        if(!m_aliments.loadFromFile(m_texture))
        {
            std::cout << "Erreur chargement aliment" << std::endl;
        }
        m_sprite_aliments.setPosition(rand() % (unQuartEcran - TailleAliment), rand() % range - 700);
    }
    else if(x == 3)
    {
        m_texture = "sushis.png";
        if(!m_aliments.loadFromFile(m_texture))
        {
            std::cout << "Erreur chargement aliment" << std::endl;
        }
        m_sprite_aliments.setPosition(rand() % (unQuartEcran - TailleAliment), rand() % range - 1900);
    }
    else if(x == 4)
    {
        m_texture = "soupe.png";
        if(!m_aliments.loadFromFile(m_texture))
        {
            std::cout << "Erreur chargement aliment" << std::endl;
        }
        m_sprite_aliments.setPosition(rand() % rangeX456 + unQuartEcran, rand() % range - 900);
    }
    else if(x == 5)
    {
        m_texture = "raviolis.png";
        if(!m_aliments.loadFromFile(m_texture))
        {
            std::cout << "Erreur chargement aliment" << std::endl;
        }
        m_sprite_aliments.setPosition(rand() % rangeX456 + unQuartEcran, rand() % range - 1300);
    }
    else if(x == 6)
    {
        m_texture = "sushis.png";
        if(!m_aliments.loadFromFile(m_texture))
        {
            std::cout << "Erreur chargement aliment" << std::endl;
        }
        m_sprite_aliments.setPosition(rand() % rangeX456 + unQuartEcran, rand() % range - 2100);
    }
    else if(x == 7)
    {
        m_texture = "soupe.png";
        if(!m_aliments.loadFromFile(m_texture))
        {
            std::cout << "Erreur chargement aliment" << std::endl;
        }
        m_sprite_aliments.setPosition(rand() % rangeX456 + moitierEcran, rand() % range - 500);
    }
    else if(x == 8)
    {
        m_texture = "poisson_pourri.png";
        if(!m_aliments.loadFromFile(m_texture))
        {
            std::cout << "Erreur chargement aliment" << std::endl;
        }
        m_sprite_aliments.setPosition(rand() % rangeX456 + moitierEcran, rand() % range - 1700);
    }
    else if(x == 9)
    {
        m_texture = "raviolis.png";
        if(!m_aliments.loadFromFile(m_texture))
        {
            std::cout << "Erreur chargement aliment" << std::endl;
        }
        m_sprite_aliments.setPosition(rand() % rangeX456 + moitierEcran, rand() % range - 2500);
    }
    else if(x == 10)
    {
        m_texture = "soupe.png";
        if(!m_aliments.loadFromFile(m_texture))
        {
            std::cout << "Erreur chargement aliment" << std::endl;
        }
        m_sprite_aliments.setPosition(rand() % rangeX456 + troisQuartEcran, rand() % range - 1100);
    }
    else if(x == 11)
    {
        m_texture = "sushis.png";
        if(!m_aliments.loadFromFile(m_texture))
        {
            std::cout << "Erreur chargement aliment" << std::endl;
        }
        m_sprite_aliments.setPosition(rand() % rangeX456 + troisQuartEcran, rand() % range - 1500);
    }
    else if(x == 12)
    {
        m_texture = "poisson_pourri.png";
        if(!m_aliments.loadFromFile(m_texture))
        {
            std::cout << "Erreur chargement aliment" << std::endl;
        }
        m_sprite_aliments.setPosition(rand() % rangeX456 + troisQuartEcran, rand() % range - 2300);
    }

    m_aliments.setSmooth(true);

    //Initialisations des attributs
    m_aliments_size = m_aliments.getSize();
    m_depasseAlimentsX = m_aliments_size.x - 30;
    m_depasseAlimentsY = m_aliments_size.y - 50;

    m_sprite_aliments.setTexture(m_aliments);

}

Aliments::~Aliments()
{

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
