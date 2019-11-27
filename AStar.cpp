#include "AStar.h"
AStar::AStar(TileMap* tilemap, sf::Vector2i goal ): tilemap(tilemap), goal(goal) {
    posInit = tilemap->getPosPlayer();
    posPlayer = tilemap->getPosPlayer();
    std::cout << "creazione di Astar" << std::endl;
}
int AStar::h_heuristic(){  //manhattan heuristic
    int dx = abs(posPlayer.x - goal.x);
    int dy = abs(posPlayer.y - goal.y);
    return dx + dy;
}
int AStar::g_distance(){
    int dx = abs(posPlayer.x - posInit.x);
    int sx = abs(posPlayer.y - posPlayer.y);
    return dx + sx;
}
int AStar::f_heuristic(){
    return g_distance() + h_heuristic();
}