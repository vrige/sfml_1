#ifndef SFML_1_ASTAR_H
#define SFML_1_ASTAR_H

#include <iostream>
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
private:
    //bool aStar();
    //store solution
    TileMap* tilemap;
    sf::Vector2i goal;
};


#endif //SFML_1_ASTAR_H
