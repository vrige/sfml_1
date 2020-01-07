//
// Created by cristina on 10/12/2019.
//

#ifndef UNIT_TESTINF_SFML_PROVA2_TILEMAP_H
#define UNIT_TESTINF_SFML_PROVA2_TILEMAP_H

#include <ctime>
#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <set>
#include <memory>
#include <vector>
#include "gtest/gtest.h"


class TileMap  : public sf::ConvexShape{
public:

    TileMap( int x, int y, int tiles, sf::Vector2u tileSize, std::shared_ptr<std::vector<int>>& mat, sf::Vector2i goal);
    TileMap( int x, int y, int tiles, sf::Vector2u tileSize, std::shared_ptr<std::vector<int>> mat, sf::Vector2i goal);


    void matXCasuale(std::shared_ptr<std::vector<int>>& matX, int x, int y, int n);
    void matXCasualeWithPercentage(std::shared_ptr<std::vector<int>>& matX, int x, int y, int n, int percentage);
    void print(std::shared_ptr<std::vector<int>>& matX, int x, int y);

    bool load(const std::string& tileset, sf::Vector2i pos);
    bool checkGridPossibileMove(char direction, sf::Vector2i posPlayer);

    sf::Vector2i  makePlayerStartGreen(sf::Vector2i posInitPlayer);
    void setGoal(sf::Vector2i newGoal,const std::string& tileset,sf::Vector2i pos);
    sf::Vector2i getGoal();
    int getValueAt(int num);
    void setValueAt(int pos, int num);
    void setValueAt(sf::Vector2i pos, int num);
    int getWidth();
    int getHeigth();

private:
    void generateGoal(sf::Vector2i pos);
    static int genRandomNumber(int n);
    static int genRandomNumberWithPercentage(int n, int percentage);

    int width,height;
    std::shared_ptr<std::vector<int>> matX;
    int tiles;
    sf::VertexArray m_vertices;
    sf::Texture m_tileset;
    sf::Vector2u m_tileSize;
    sf::Vector2i goal;
    bool isThereAGoal;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();

        states.texture = &m_tileset;

        target.draw(m_vertices, states);
    }
};


#endif //UNIT_TESTINF_SFML_PROVA2_TILEMAP_H
