#ifndef SFML_1_ASTAR_H
#define SFML_1_ASTAR_H

#include <cstdlib>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <iterator>
#include <unordered_map>
#include "TileMap.h"

class AStar {
    //la soluzione dovrà in qualche modo essere raccolta ed utilizzata per mostrare che graficamente il player arriva al goal (oppure no)
    //Dopo di ciò marcare il path con un colore diverso

public:
    AStar(TileMap* tilemap, sf::Vector2i goal);
    bool astar();
    void provaEuristiche();
    std::vector<int> getPath();
    std::vector<char> getEasierToReadPath();
private:
    int h_heuristic(sf::Vector2i pos);
    int h_heuristic(int pos);
    int g_distance(sf::Vector2i pos);
    int g_distance(int pos);
    int f_heuristic(sf::Vector2i pos);
    int f_heuristic(int pos);
    std::set<int> checkChildren(sf::Vector2i pos);
    std::set<int> checkChildren(int pos);
    int getTheMinorFfromSet(std::set<int> set);
    std::vector<int> reconstruct_path(std::unordered_map<int, int> came_from);
    std::vector<char> reconstruct_EasierToReadPath();


    TileMap* tilemap;
    int width;
    int heigth;
    sf::Vector2i goal;
    sf::Vector2i posInit;
    sf::Vector2i posPlayer;
    std::vector<int> path;
    std::vector<char> easierToReadPath;
};


#endif //SFML_1_ASTAR_H
