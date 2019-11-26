
#ifndef SFML_1_PLAYER_H
#define SFML_1_PLAYER_H


#include <SFML/Graphics.hpp>
#include <iostream>

class Player : public sf::RectangleShape
{
public:
    Player(const std::string& texture, sf::Vector2u playerSize);
    void movePlayer(char direction);
    sf::Sprite getSprite();
    sf::Vector2i getPos();
    void setPos(sf::Vector2i pos); //la posizione non è in pixel, ma è data dalla coppia i e j del tile
    void setPos(int x, int y);
    void setPosizione(sf::Vector2f pos); //cambia la posizione della sprite
    void setPosizione(float x, float y);
    bool getIsMoved();
    void setIsMoved(bool isMoved);
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        target.draw(m_sprite, states);
    }

    sf::Sprite m_sprite;
    sf::Texture m_texture;
    sf::Vector2i pos;
    sf::Vector2u playerSize;
    bool isMoved;
};



#endif //SFML_1_PLAYER_H
