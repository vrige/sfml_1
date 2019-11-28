#ifndef SFML_1_ASTAR_H
#define SFML_1_ASTAR_H

#include <cstdlib>
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <iterator>
#include "TileMap.h"

class AStar {
    //meglio provare a riscrivre da capo aStar
//deve prendere una classe di problemi e rendere una soluzione
//scrivere una funzione in TileMap che crei un goal oppure passare un goal sicuro come paramentro ad AStar
//la soluzione dovrà in qualche modo essere raccolta ed utilizzata per mostrare che graficamente il player arriva al goal (oppure no)
//Dopo di ciò marcare il path con un colore diverso
//Infine fare in modo che premendo il tasto A si azioni AStar
public:
    AStar(TileMap* tilemap, sf::Vector2i goal);
    //getSolution()
    void astar();
private:
    int h_heuristic(sf::Vector2i pos);
    int h_heuristic(int pos);
    int g_distance(sf::Vector2i pos);
    int f_heuristic(sf::Vector2i pos);
    int f_heuristic(int pos);
    std::set<int> checkChildren(sf::Vector2i pos);
    std::set<int> checkChildren(int pos);
    int getTheMinorFfromChildren(std::set<int> children);
    //bool aStar&();
    //store solution

    TileMap* tilemap;
    int width;
    int heigth;
    sf::Vector2i goal;
    sf::Vector2i posInit;
    sf::Vector2i posPlayer;


};


#endif //SFML_1_ASTAR_H
