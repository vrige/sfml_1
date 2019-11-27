#ifndef SFML_1_TILEMAP_H
#define SFML_1_TILEMAP_H

#include <ctime>
#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <set>
#include "Player.h"

class TileMap  : public sf::ConvexShape{
public:

    TileMap( int x, int y, int tiles, sf::Vector2u tileSize, Player* player);
    TileMap( int x, int y, int tiles,sf::Vector2u tileSize, int percentualeZeri, Player* player);

    virtual ~TileMap();

    static void matXCasuale(int* matX, int x, int y, int n);
    static void matXCasualeWithPercentage(int* matX, int x, int y, int n, int percentage);

    bool load(const std::string& tileset, sf::Vector2i pos);
    bool checkGridPossibileMove(char direction);

    sf::Vector2i getGoal();

    template <class myType>
        static void print(const myType* matX,const int x, const int y){
            std::string a = "";
            for(int j = 0; j < y; j++){
                for(int i = 0; i < x; i++){
                    if(typeid(int) == typeid(myType)){
                        a += std::to_string(matX[i + j * x]) + " ";
                    }
                    else if(typeid(char) == typeid(myType)){
                        a += matX[i + j * x];
                        a += " ";
                    }
                }
                std::cout<< a <<std::endl;
                a = "";
            }
            std::cout<<std::endl;
        }
private:
    void generateGoal();
    bool playerStartGreen(sf::Vector2i pos);
    static int genRandomNumber(int n);
    static int genRandomNumberWithPercentage(int n, int percentage);

    int width,height;
    int* matX;
    int tiles;
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
    sf::Vector2u m_tileSize;
    Player* player;
    sf::Vector2i goal;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();

        states.texture = &m_tileset;

        target.draw(m_vertices, states);
    }
};


#endif //SFML_1_TILEMAP_H
