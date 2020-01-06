//
// Created by cristina on 10/12/2019.
//

#include "AStar.h"
AStar::AStar(TileMap* tilemap,  Player* player, sf::Vector2i goal ): tilemap(tilemap),player(player),goal(goal) {
    width = tilemap->getWidth();
    heigth = tilemap->getHeigth();
    posInit = player->getPosInMatrix();
    std::cout << "creazione di Astar" << std::endl;
}
AStar::~AStar(){
    std::cout<<"delete tilemap and player"<<std::endl;
    delete tilemap;
    delete player;
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
bool AStar::findPath() {
    posInit = player->getPosInMatrix();
    std::set<int> openList;

    std::unordered_map<int, int> cost_so_far;
    std::unordered_map<int, int> came_from;

    int start = posInit.x + posInit.y * width;
    openList.insert(start);
    cost_so_far[start] = 0;
    came_from[start] = start;

    int current = -1;

    while(!openList.empty()){
        current = getTheMinorFromSet(openList, cost_so_far);
        openList.erase(current);

        if(h_heuristic(current) == 0) { //è il goal!
            std::cout << "goal trovato!" << std::endl;
            break;
        }else{
            std::set<int> children = checkChildren(current);
            for(int child : children){
                int tile_cost = (tilemap->getValueAt(child) % 5) * 20;
                int cost = cost_so_far[current] + tile_cost;

                if (cost_so_far.find(child) == cost_so_far.end()) {
                    cost_so_far[child] = cost;
                    openList.insert(child);
                    came_from[child] = current;
                }

            }
        }
    }
    if(current == goal.x + goal.y * width){
        std::cout<<"goal trovato! Ora calcoliamo il path" << std::endl;
        path = reconstruct_path(came_from);
        easierToReadPath = reconstruct_EasierToReadPath();
        std::cout<<"sei contento di aver trovato il goal?!" << std::endl;
        return true;
    }else{
        std::cout<<"goal non trovato!" << std::endl;
        path.clear();
        easierToReadPath.clear();
        return false;
    }
}
void AStar::testHeuristics(){
    int pos = player->getPosInMatrix().x +player->getPosInMatrix().y * width;
    std::cout<<"posizione attuale "<<player->getPosInMatrix().x <<" " <<player->getPosInMatrix().y;
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
    return checkChildren(pos.x + pos.y * width);
}
std::set<int> AStar::checkChildren(int pos){
    std::set<int> children;
    std::set<char> moves = {'u','r','d','l'};
    sf::Vector2i posPlayer = sf::Vector2i(pos % width,pos / width);
    for(char move : moves){
        if(tilemap->checkGridPossibileMove(move, posPlayer)){
            switch(move){
                case 'u':
                    children.insert(pos - width);
                    break;
                case 'r':
                    children.insert(pos + 1);
                    break;
                case 'd':
                    children.insert(pos + width);
                    break;
                case 'l':
                    children.insert(pos - 1);
                    break;
                default:
                    std::cout<<"c'è qualche problema nel checkChildren"<<std::endl;
            }
        }
    }
    return children;
}
int AStar::getTheMinorFromSet(std::set<int> set, std::unordered_map<int, int> cost_so_far){
    if(!set.empty()){
        int min = 100000;
        int minEle = -1;
        for(int iter : set){
            // std::cout<<"pos: "<<iter<<" value of f: " << f_heuristic(iter)<<std::endl;
            if(cost_so_far[iter] + f_heuristic(iter) < min){  //notare che non viene utilizzata f_heurisitc perchè
                min = cost_so_far[iter] + f_heuristic(iter);  //in cost_so_far c'è già g_heuristic, quindi basta utilizzare
                minEle = iter;                                //h_heuristic
            }
        }
        return minEle;
    }else{
        std::cout<<"il set fornito è vuoto!"<<std::endl;
        return -1;
    }
}
std::vector<int> AStar::reconstruct_path(std::unordered_map<int, int> came_from){
    std::cout<<"reostruct_path start"<<std::endl;
    std::vector<int> pathh;
    int current = goal.x + goal.y*width;
    int start = posInit.x + posInit.y * width;
    while (current != start) {
        std::cout<<current<<std::endl;
        pathh.push_back(current);
        current = came_from[current];
    }
    pathh.push_back(start); // optional
    std::reverse(pathh.begin(), pathh.end());
    std::cout<<"reostruct_path"<<std::endl;
    return pathh;
}
std::vector<char> AStar::reconstruct_EasierToReadPath(){
    std::vector<char> dir;
    for(auto it = path.begin() ; it != (path.end() - 1) ; ++it){

        int direction = *it - *(it + 1);

        if(direction == 1) {//left
            dir.push_back('l');
        }
        else if(direction == -1) { //rigth
            dir.push_back('r');
        }
        else if(direction == width){ //up
            dir.push_back('u');
        }
        else if(direction == -width){ //down
            dir.push_back('d');
        }else{
            std::cout<<"problemi nel geteasierToReadPath"<<std::endl;
        }
    }
    std::cout<<"reostruct_EasierToReadPath"<<std::endl;
    return dir;
}
std::vector<int> AStar::getPath(){
    return path;
}
std::vector<char> AStar::getEasierToReadPath(){
    return easierToReadPath;
}