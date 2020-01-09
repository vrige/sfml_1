#ifndef UNIT_TESTINF_SFML_PROVA2_ASTAR_H
#define UNIT_TESTINF_SFML_PROVA2_ASTAR_H

#include <cstdlib>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <iterator>
#include <unordered_map>
#include <memory>
#include "RenderingMap.h"
#include "Player.h"
#include "gtest/gtest.h"

class AStar {
public:
    AStar(std::shared_ptr<RenderingMap>& tilemap, std::shared_ptr<Player>& player, sf::Vector2i goal );
    bool findPath();
    std::vector<int> getPath();
    std::vector<char> getEasierToReadPath();
    void setGoal(sf::Vector2i newGoal,const std::string& tileset);
    void setAstar(std::shared_ptr<std::vector<int>>& mat, int x, int y, sf::Vector2i goal, const std::string& tileset,sf::Vector2i pos);
private:
    int h_heuristic(sf::Vector2i pos);
    int h_heuristic(int pos);
    int g_distance(sf::Vector2i pos);
    int g_distance(int pos);
    int f_heuristic(sf::Vector2i pos);
    int f_heuristic(int pos);
    std::set<int> checkChildren(sf::Vector2i pos);
    std::set<int> checkChildren(int pos);
    int getTheMinorFromSet(std::set<int> set, std::unordered_map<int, int> cost_so_far);
    std::vector<int> reconstruct_path(std::unordered_map<int, int> came_from);
    std::vector<char> reconstruct_EasierToReadPath();


    std::shared_ptr<RenderingMap> tilemap;
    std::shared_ptr<Player> player;
    int width;
    int heigth;
    sf::Vector2i goal;
    sf::Vector2i posInit;
    std::vector<int> path;
    std::vector<char> easierToReadPath;
};

#endif //UNIT_TESTINF_SFML_PROVA2_ASTAR_H
