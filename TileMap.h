#ifndef SFML_1_TILEMAP_H
#define SFML_1_TILEMAP_H

#include <ctime>
#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <set>
#include <memory>


class TileMap  : public sf::ConvexShape{
public:

    TileMap( int x, int y, int tiles, sf::Vector2u tileSize);
    TileMap( int x, int y, int tiles,sf::Vector2u tileSize, int percentualeZeri);
    TileMap( int x, int y, int tiles, sf::Vector2u tileSize, std::unique_ptr<int[]>& matX);


    static void matXCasuale(std::unique_ptr<int[]>& matX, int x, int y, int n);
    static void matXCasualeWithPercentage(std::unique_ptr<int[]>& matX, int x, int y, int n, int percentage);
    static void print(std::unique_ptr<int[]>& matX, int x, int y);

    bool load(const std::string& tileset, sf::Vector2i pos);
    bool checkGridPossibileMove(char direction, sf::Vector2i posPlayer);

    sf::Vector2i  makePlayerStartGreen(sf::Vector2i posInitPlayer);

    sf::Vector2i getGoal();
    int getValueAt(int matx);
    int getWidth();
    int getHeigth();

private:
    void generateGoal(sf::Vector2i pos);
    static int genRandomNumber(int n);
    static int genRandomNumberWithPercentage(int n, int percentage);

    int width,height;
    std::unique_ptr<int[]> matX;
    int tiles;
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
    sf::Vector2u m_tileSize;
    sf::Vector2i goal;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();

        states.texture = &m_tileset;

        target.draw(m_vertices, states);
    }
};


#endif //SFML_1_TILEMAP_H
