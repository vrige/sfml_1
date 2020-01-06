//
// Created by cristina on 10/12/2019.
//

#include "Player.h"
Player::Player(const std::string& texture, sf::Vector2u playerSize){
    //102 e 0 indica la posizione dell'angolo sinistro del ritaglio per la texture
    //(basta utilizzare dei multipli di 34--> vedi img/game34x34.png)
    if(!m_texture.loadFromFile(texture, sf::IntRect(102,0,playerSize.x,playerSize.y))){
        std::cout<<"failed to download the texture"<< std::endl;
    }
    m_sprite.setTexture(m_texture);
    this->playerSize = playerSize;
    this->isMoved = false;
}
void Player::movePlayer(char direction){
    isMoved = true;

    int x = posPlayer.x;
    int y = posPlayer.y;
    float xf = posPlayer.x;
    float yf = posPlayer.y;

    switch(direction){
        case 'u':
            setPosInMatrix(x, y - 1);
            setPosInSprite(xf * playerSize.x, (yf - 1)* playerSize.y);
            break;
        case 'd':
            setPosInMatrix(x, y + 1);
            setPosInSprite(xf * playerSize.x, (yf + 1)* playerSize.y);
            break;
        case 'l':
            setPosInMatrix(x - 1, y);
            setPosInSprite((xf - 1)* playerSize.x, yf* playerSize.y);
            break;
        case 'r':
            setPosInMatrix(x + 1,y);
            setPosInSprite((xf + 1)* playerSize.x,yf* playerSize.y);
            break;
        default:
            std::cout<<"problemi nella scelta della direzione"<<std::endl;
    }
}
sf::Sprite Player::getSprite(){
    return m_sprite;
}
sf::Vector2i Player::getPosInMatrix(){
    return this->posPlayer;
}
void Player::setPosInMatrix(sf::Vector2i poss){
    this->posPlayer = poss;
}
void Player::setPosInMatrix(int x, int y){
    this->posPlayer = sf::Vector2i(x,y);
}
void Player::setPosInSprite(sf::Vector2f poss){
    m_sprite.setPosition(poss);
}
void Player::setPosInSprite(float x, float y){
    m_sprite.setPosition(x,y);
}
bool Player::getIsMoved(){
    return isMoved;
}
void Player::setIsMoved(bool isMovedd){
    this->isMoved = isMovedd;
}
sf::Vector2u Player::getPlayerSize(){
    return playerSize;
}