#include <grid.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

namespace battlespace{

    Grid::Grid(){
        for (int i=0 ; i<10 ; i++){
            grid.push_back(std::vector<std::string>());
        }
        for (auto &v :grid){
            for (int i=0 ; i<10 ; i++){
                v.push_back("o");

            }
        }

        toPlace.insert(battlespace::Ship(0,5));
        toPlace.insert(battlespace::Ship(1,4));
        toPlace.insert(battlespace::Ship(2,3));
        toPlace.insert(battlespace::Ship(3,3));
        toPlace.insert(battlespace::Ship(4,2));
    }
     std::vector<std::vector<std::string>> Grid::getGrid(){
        return grid;
    }

    std::vector<std::vector<std::string>> Grid::getGridFogOfWar(){
        std::vector<std::vector<std::string>> ret;
        ret = grid;
        for(auto &v :ret){
            for(auto &s : v){
                if(s != "o" && s != "m" && s!= "x"){
                    s = "o";
                }
            }
            std::cout<< ""<< std::endl;
        }
        return ret;
    }

    void Grid::print()const{
        for(auto &v :grid){
            for(auto &s : v){
                std::cout << s ;
            }
            std::cout<< ""<< std::endl;
        }
    }

    bool Grid::placeShip(int shipId,std::pair<int,int> pos1,std::pair<int,int> pos2){
        //big block of illegal case checks

        auto it = std::find_if(toPlace.begin(), toPlace.end(),
                       [shipId](const Ship &s) { return s.id == shipId; });
        if (it == toPlace.end()) return false; // Ship is not in the set
        if(pos1.first > 9 || pos1.first < 0) return false; //makes sure given positions are in bounds
        if(pos1.second > 9 || pos1.second < 0) return false;
        if(pos2.first > 9 || pos2.first < 0) return false;
        if(pos2.second > 9 || pos2.second < 0) return false;
        if(pos1.first==pos2.first){ //horizontal case
            if(it->size != pos2.second-pos1.second+1) return false; // if ship is not the correct length
        }else if(pos1.second==pos2.second){ //vertical case
            if(it->size != pos2.first-pos1.first+1) return false; // if ship is not the correct length
        }else if(pos1.first != pos2.first && pos1.second != pos2.second) return false; //diagonal ships

        bool unobstructed = true;
        if(pos1.first == pos2.first){ //horizontal case
            for (int i=pos1.second; i<=pos2.second ;i++){
                if(grid[pos1.first][i]!="o"){ //if the space the ship will occupy does not only contain empty spaces
                    unobstructed = false;
                }
            }
            if(unobstructed){ //all checks are passed, the ship is placed
                for (int i=pos1.second; i<=pos2.second ;i++){
                    grid[pos1.first][i] = std::to_string(shipId);
                }
                toPlace.erase(it);
                placed.insert(battlespace::Ship(shipId,pos2.second-pos1.second+1));
                return true;
            }
        }else if(pos1.second == pos2.second){ //vertical case
            for (int i=pos1.first; i<=pos2.first ;i++){
                if(grid[i][pos1.second]!="o"){ //if the space the ship will occupy does not only contain empty spaces
                    unobstructed = false;
                }
            }
            if(unobstructed){ //all checks are passed, the ship is placed
                for (int i=pos1.first; i<=pos2.first ;i++){
                    grid[i][pos1.second] = std::to_string(shipId);
                }
                toPlace.erase(it);
                placed.insert(battlespace::Ship(shipId,pos2.first-pos1.first+1));
                return true;
            }
        }
        return false;
    }

 //@return 0:hit 1:miss 2:out of bounds 3:repeat hit 4:hit and sink  5:error 6:winning shot
    int Grid::shootAt(std::pair<int,int>shot){
            if(shot.first > 9 || shot.first < 0) return 2; //makes sure given coordinates are in bounds
            if(shot.second > 9 || shot.second < 0) return 2;
            if(grid[shot.first][shot.second] == "o") {
                grid[shot.first][shot.second] = "m";
                return 1;
            }
            if(grid[shot.first][shot.second] == "m" || grid[shot.first][shot.second] == "x") return 3;
            int remainingParts=0;
            for(auto &v :grid){ //cont alive parts of hit ship
                for(auto &s : v){
                    if (s == grid[shot.first][shot.second]) remainingParts++;
                }
            }
            if(remainingParts>1){
                grid[shot.first][shot.second] = "x";
                return 0;
            }

            // Convert stored string in grid to an integer
            int shipId = std::stoi(grid[shot.first][shot.second]);

            // Search for the matching ship in placed
            auto it = std::find_if(placed.begin(), placed.end(),
                [shipId](const Ship &s) { return s.id == shipId; });

            if (it == placed.end()) return 5; // Ship not found, probably an error
            placed.erase(it);
            grid[shot.first][shot.second] = "x";
            if(placed.empty()){
                return 6;
            }
            return 4;
    }

    bool Grid::getReady(){
        return toPlace.empty();
    }
}
































