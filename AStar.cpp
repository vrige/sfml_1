#include "AStar.h"

AStar::AStar(TileMap* tilemap, sf::Vector2i goal ): tilemap(tilemap), goal(goal) {
    width = tilemap->getWidth();
    heigth = tilemap->getHeigth();
    posInit = tilemap->getPosPlayer();
    posPlayer = tilemap->getPosPlayer();
    std::cout << "creazione di Astar" << std::endl;
}
int AStar::h_heuristic(sf::Vector2i pos){  //manhattan heuristic
    int dx = abs(pos.x - goal.x);
    int dy = abs(pos.y - goal.y);
    return dx + dy;
}
int AStar::h_heuristic(int pos){  //manhattan heuristic

    int dx = abs(pos%width - goal.x);
    int dy = abs(pos/width - goal.y);
  //  std::cout << "pos H_: "<<pos%width << " " << pos/width << "  h:" << dx+dy << std::endl;
    return dx + dy;
}
int AStar::g_distance(sf::Vector2i pos){
    int dx = abs(pos.x - posInit.x);
    int sx = abs(pos.y - posInit.y);
    return dx + sx;
}
int AStar::f_heuristic(sf::Vector2i pos){
    return g_distance(pos) + h_heuristic(pos);
}
int AStar::f_heuristic(int pos){
    sf::Vector2i posVec(pos%width, pos/width);
    //std::cout<<"pos f_: " << pos/width << " " << pos%width << std::endl;
    return f_heuristic(posVec);
}
void AStar::astar() {
    std::vector<char> direzioni;

/*    std::set<Node> openList;
    std::set<Node> closeList;*/
    std::set<int> children = checkChildren(tilemap->getPosPlayer().x + tilemap->getPosPlayer().y * width);
    int min = getTheMinorFfromChildren(children);
    if(min != -1){

    }

    //o decido di usare sempre i nodi per queste funzioni oppure utilizzo la posizione che hanno nella matrice
    //non ho bisogno della classe nodo perchè:
    //- i figli posso vederli dalla matrice
    //- f dei nodi non cambia quindi posso mapparlo
    //- le direzioni le salvo come char su un vector
    //- in openlist e clsoelist ci inserisco i valori di pos della matrice

}
std::set<int> AStar::checkChildren(sf::Vector2i pos){
    checkChildren(pos.x + pos.y * width);
}
std::set<int> AStar::checkChildren(int pos){
    std::set<int> children;
    if(tilemap->getValueAt(pos + 1) == 0 || tilemap->getValueAt(pos + 1) == 5){ //right
        std::cout<<"dx libera"<<std::endl;
        children.insert(pos + 1);
    }
    if(tilemap->getValueAt(pos - 1) == 0 || tilemap->getValueAt(pos - 1) == 5) { //left
        std::cout<<"sx libera"<<std::endl;
        children.insert(pos - 1);
    }
    if(tilemap->getValueAt(pos + width) == 0 || tilemap->getValueAt(pos + width) == 5) { //down
        std::cout<<"dw libera"<<std::endl;
        children.insert(pos + width);
    }
    if((tilemap->getValueAt(pos - width) == 0 && tilemap->checkGridPossibileMove('u'))|| tilemap->getValueAt(pos - width) == 5) { //up
        std::cout<<"up libera"<<std::endl;
        children.insert(pos - width);
    }
    return children;
}
int AStar::getTheMinorFfromChildren(std::set<int> children){
    if(!children.empty()){
        int min = 100000;
        for(int iter : children){
            std::cout<<"pos: "<<iter<<" value of f: " << h_heuristic(iter)<<std::endl;
            if(h_heuristic(iter) < min){
                min = h_heuristic(iter);
            }
        }
        return min;
    }else{
        std::cout<<"il set fornito è vuoto!"<<std::endl;
        return -1;
    }
}