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
int AStar::g_distance(int pos){
    int dx = abs(pos%width - posInit.x);
    int sx = abs(pos/width - posInit.y);
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

    std::set<int> openList;
    std::set<int> closeList;

    int start = tilemap->getPosPlayer().x + tilemap->getPosPlayer().y * width;
    openList.insert(start);

    int current = -1;

    while(!openList.empty()){
        current = getTheMinorFfromSet(openList);
        openList.erase(current);

        if(h_heuristic(current) == 0) { //è il goal!
            std::cout << "goal trovato!" << std::endl;
            break;
        }else{
            std::set<int> children = checkChildren(current);
            for(int child : children){
                int cost = g_distance(child) + 1;
                if(openList.find(child) != openList.end()) {
                    if (g_distance(child) <= cost) {

                    }
                    continue;
                }else if(closeList.find(child) != closeList.end()){
                    if(g_distance(child) <= cost){
                        closeList.erase(child);
                        openList.insert(child);
                    }
                    continue;
                }else {
                    openList.insert(child);
                }
            }

        }
        closeList.insert(current);
    }
    if(current == goal.x + goal.y * width){
        std::cout<<"sei contento di aver trovato il goal?!" << std::endl;
    }



    //o decido di usare sempre i nodi per queste funzioni oppure utilizzo la posizione che hanno nella matrice
    //non ho bisogno della classe nodo perchè:
    //- i figli posso vederli dalla matrice
    //- f dei nodi non cambia quindi posso mapparlo
    //- le direzioni le salvo come char su un vector
    //- in openlist e clsoelist ci inserisco i valori di pos della matrice


    // a star deve tenere il segno di dove si dovrebbe spostare il personaggio
}
void  AStar::provaEuristiche(){
    int pos = tilemap->getPosPlayer().x + tilemap->getPosPlayer().y * width;
    std::cout<<"posizione attuale "<<tilemap->getPosPlayer().x <<" " <<tilemap->getPosPlayer().y;
    std::cout<<"  g: "<<g_distance(pos);
    std::cout<<",  h: "<<h_heuristic(pos);
    std::cout<<",  f: "<<f_heuristic(pos)<<std::endl;

    std::set<int> children = checkChildren(pos);
    for(int child : children){
        std::cout<<"figlio "<<child<<" in pos: "<< child << ", g: "<< g_distance(child) << ", h: " << h_heuristic(child);
        std::cout<<", f: "<< f_heuristic(child)<< std::endl;
    }
}
std::set<int> AStar::checkChildren(sf::Vector2i pos){
    checkChildren(pos.x + pos.y * width);
}
std::set<int> AStar::checkChildren(int pos){
    std::set<int> children;
    if(tilemap->getValueAt(pos + 1) == 0 || tilemap->getValueAt(pos + 1) == 5){ //right
       // std::cout<<"dx libera"<<std::endl;
        children.insert(pos + 1);
    }
    if(tilemap->getValueAt(pos - 1) == 0 || tilemap->getValueAt(pos - 1) == 5) { //left
      //  std::cout<<"sx libera"<<std::endl;
        children.insert(pos - 1);
    }
    if(tilemap->getValueAt(pos + width) == 0 || tilemap->getValueAt(pos + width) == 5) { //down
       // std::cout<<"dw libera"<<std::endl;
        children.insert(pos + width);
    }
    if(tilemap->getValueAt(pos - width) == 0 || tilemap->getValueAt(pos - width) == 5) { //up
        //std::cout<<"up libera"<<std::endl;
        children.insert(pos - width);
    }
    return children;
}
int AStar::getTheMinorFfromSet(std::set<int> set){
    if(!set.empty()){
        int min = 100000;
        int minEle = -1;
        for(int iter : set){
            std::cout<<"pos: "<<iter<<" value of f: " << f_heuristic(iter)<<std::endl;
            if(f_heuristic(iter) < min){
                min = f_heuristic(iter);
                minEle = iter;
            }
        }
        return minEle;
    }else{
        std::cout<<"il set fornito è vuoto!"<<std::endl;
        return -1;
    }
}