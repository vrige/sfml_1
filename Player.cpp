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

    int x = pos.x;
    int y = pos.y;
    float xf = pos.x;
    float yf = pos.y;

    switch(direction){
        case 'u':
            setPos(x, y - 1);
            setPosizione(xf * playerSize.x, (yf - 1)* playerSize.y);
            break;
        case 'd':
            setPos(x, y + 1);
            setPosizione(xf * playerSize.x, (yf + 1)* playerSize.y);
            break;
        case 'l':
            setPos(x - 1, y);
            setPosizione((xf - 1)* playerSize.x, yf* playerSize.y);
            break;
        case 'r':
            setPos(x + 1,y);
            setPosizione((xf + 1)* playerSize.x,yf* playerSize.y);
            break;
        default:
            std::cout<<"problemi nella scelta della direzione"<<std::endl;
    }
}
sf::Sprite Player::getSprite(){
    return m_sprite;
}
sf::Vector2i Player::getPos(){
    return this->pos;
}
void Player::setPos(sf::Vector2i poss){
    this->pos = poss;
}
void Player::setPos(int x, int y){
    this->pos = sf::Vector2i(x,y);
}
void Player::setPosizione(sf::Vector2f poss){
    m_sprite.setPosition(poss);
}
void Player::setPosizione(float x, float y){
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