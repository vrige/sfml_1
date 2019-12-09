#include "AStar.h"

AStar::AStar(TileMap* tilemap,  Player* player, sf::Vector2i goal ): tilemap(tilemap),player(player),goal(goal) {
    width = tilemap->getWidth();
    heigth = tilemap->getHeigth();
    posInit = player->getPosInMatrix();
    posPlayer = player->getPosInMatrix();
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

    std::unordered_map<int, double> cost_so_far;
    std::unordered_map<int, int> came_from;

    int start = player->getPosInMatrix().x + player->getPosInMatrix().y * width;
    openList.insert(start);
    cost_so_far[start] = 0;
    came_from[start] = start;

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

                if (cost_so_far.find(child) == cost_so_far.end()
                    || cost < cost_so_far[child]) {
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
           // std::cout<<"pos: "<<iter<<" value of f: " << f_heuristic(iter)<<std::endl;
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
std::vector<int> AStar::reconstruct_path(std::unordered_map<int, int> came_from){
    std::vector<int> pathh;
    int current = goal.x + goal.y*width;
    int start = posInit.x + posInit.y * width;
    while (current != start) {
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
    for(std::vector<int>::iterator it = path.begin() ; it != (path.end() - 1) ; ++it){

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