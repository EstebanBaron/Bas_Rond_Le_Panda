#ifndef PIECE_H_INCLUDED
#define PIECE_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>

class Piece
{
    public :
    Piece();
    ~Piece();
    sf::Sprite getSpritePiece() const;

    private :
    sf::Texture m_piece;
    sf::Sprite m_sprite_piece;
    sf::Vector2u m_piece_size;
};

#endif // PIECE_H_INCLUDED
