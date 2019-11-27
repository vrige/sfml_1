#include "AStar.h"
AStar::AStar(TileMap* tilemap, sf::Vector2i goal ): tilemap(tilemap), goal(goal){
    std::cout<<"creazione di Astar"<< std::endl;
}
