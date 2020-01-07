//
// Created by cristina on 10/12/2019.
//

#ifndef UNIT_TESTINF_SFML_PROVA2_PLAYER_H
#define UNIT_TESTINF_SFML_PROVA2_PLAYER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "gtest/gtest.h"

class Player : public sf::RectangleShape
{
public:
    Player(const std::string& texture, sf::Vector2u playerSize);
    void movePlayer(char direction);
    sf::Sprite getSprite();
    sf::Vector2i getPosInMatrix();
    void setPosInMatrix(sf::Vector2i pos); //la posizione non è in pixel, ma è data dalla coppia i e j del tile
    void setPosInMatrix(int x, int y);
    void setPosInSprite(sf::Vector2f pos); //cambia la posizione della sprite
    void setPosInSprite(float x, float y);
    bool getIsMoved();
    void setIsMoved(bool isMoved);
    sf::Vector2u getPlayerSize();

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(m_sprite, states);
    }

    sf::Sprite m_sprite;
    sf::Texture m_texture;
    sf::Vector2i posPlayer;
    sf::Vector2u playerSize;
    bool isMoved;
};



#endif //UNIT_TESTINF_SFML_PROVA2_PLAYER_H
