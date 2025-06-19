#include <game.hpp>
#include <grid.hpp>
#include <ship.hpp>

namespace battlespace {
    Game::Game(int gameId){
        id = gameId;
        grid1 = battlespace::Grid();
        grid2 = battlespace::Grid();
        players.first = 0;
        players.second = 0;
        active = false;
    }

    bool Game::join(int playerId){
        if(players.first == 0){ //if first player slot is empty, fill it
            players.first = playerId;
            participants.insert(playerId);
            return true;
        }else if(!(players.first == 0 ) && !(players.first == playerId)&& players.second == 0){ //if first player slot is filled by somebody other that joining player, fill slot
            players.second = playerId;
            participants.insert(playerId);
            return true;
        }
        participants.insert(playerId); // if both player slots are fille add joiner to participants as a spectator
        return false;
    }

    bool Game::startGame(){
        if(players.second != 0 ){ //if two players are present, and all ships have been placed, start the game
            active = true;
            currentPlayer=players.first;
        }
        return active;
    }


    std::pair<std::vector<std::vector<std::string>>,std::vector<std::vector<std::string>>> Game::getState(int id){
        std::pair<std::vector<std::vector<std::string>>,std::vector<std::vector<std::string>>> ret;
        if(id != players.first && id != players.second){
            ret.first = grid1.getGridFogOfWar();
            ret.second = grid2.getGridFogOfWar();
        }else if(id == players.first){
             ret.first = grid1.getGrid();
             ret.second = grid2.getGridFogOfWar();
        }else if(id == players.second){
             ret.first = grid1.getGridFogOfWar();
             ret.second = grid2.getGrid();
        }
        return ret;
    }

    std::set<int> Game::getParticipants(){
        return participants;
    }

    bool Game::placeShip(int playerId,int shipId,std::pair<int,int> pos1,std::pair<int,int> pos2){
        if(playerId == players.first){
            return grid1.placeShip(shipId,pos1,pos2);
        }
        if(playerId == players.second){
            return grid2.placeShip(shipId,pos1,pos2);
        }
        return false;
    }
     //-1:not a player 0:hit 1:miss 2:out of bounds 3:repeat hit 4:hit and sink 5:error 6:wining move 7:not all ships have been placed
    int Game::makeMove(int playerId, std::pair<int,int> shot){
        if(!(grid1.getReady() && grid2.getReady())) return 7; //if one or both of the bords is not ready to play
        int outcome=-1;
        if(playerId == currentPlayer){
            if (currentPlayer == players.first){
                outcome = grid2.shootAt(shot);
            }else{
                outcome = grid1.shootAt(shot);
            }
            if(outcome == 1){
                if(currentPlayer == players.first){
                    currentPlayer = players.second;
                }else{
                    currentPlayer = players.first;
                }
            }
        }
        return outcome;
    }

    int Game::getNextPlayer(){
        return currentPlayer;
    }
}



