#include "Piece.h"

//Variables
int const largeurFenetre = 700;

//Méthodes
Piece::Piece()
{
    if(!m_piece.loadFromFile("piece.png"))
    {
        std::cout << "Erreur chargement piece" << std::endl;
    }

    m_piece_size = m_piece.getSize();
    m_sprite_piece.setTexture(m_piece);
    m_sprite_piece.setPosition(largeurFenetre - (2 *m_piece_size.x),4);
}

Piece::~Piece()
{

}

sf::Sprite Piece::getSpritePiece() const
{
    return m_sprite_piece;
}
