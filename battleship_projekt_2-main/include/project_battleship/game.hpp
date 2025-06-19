#pragma once
#include <vector>
#include <string>
#include <utility>
#include <set>
#include <ship.hpp>
#include <grid.hpp>

namespace battlespace {
    /**
    * @brief Represents a Battleship game session.
    */
    class Game {
        public:

            /**
            * @brief Constructs a new Game object with the given game ID.
            * @param gameId The unique ID for the game.
            */
            Game(int gameId);

            /**
            * @brief Places a ship for the specified player.
            * @param shipid id of ship to be placed
            * @param playerId The player's ID.
            * @param pos1 starting position of placed ship
            * @param pos2 end of placed ship
            * @return True if the ship was placed successfully, false otherwise (e.g., overlap).
            */
            bool placeShip(int playerId,int shipId,std::pair<int,int> pos1,std::pair<int,int> pos2);

            /**
            * @brief Player makes a move (fires at a cell).
            * @param playerId The player's ID making the move.
            * @param shot std::pair<int,int> containing x then y coordinates of the shot
            * @return -1:not a player 0:hit 1:miss 2:out of bounds 3:repeat hit 4:hit and sink 5:error 6:win
            */
            int makeMove(int playerId, std::pair<int,int> shot);

            /**
            * @brief Gets a summary of the current game state (e.g., for the REST API).
            * @param int id id of requesting player
            * @return pair of two dimentional vectors containing the game states, apropriately censored for requesting player
            */
            std::pair<std::vector<std::vector<std::string>>,std::vector<std::vector<std::string>>> getState(int id);

            /**
            * @brief lets players join the game, only first two are considered eligeble to make moves
            * @param pladerId if of joining Player
            * @return true if successfully joined as a player, false otherwise (playerId will still be added to participants)
            */
            bool join(int playerId);

            /**
            * @brief starts game if two players are present and all ships have been placed
            * @return true if game was started, false otherwise
            */
            bool startGame();

            /**
            * @brief get participants, who need to be notified about gamestate changes
            * @return std::set<int> of all players who have joined
            */
            std::set<int> getParticipants();

            /**
             * @brief returns id of player next to move
             * @return id of active player
             */
            int getNextPlayer();

        private:
            bool active;
            int id;                        ///< Unique game ID
            std::set<int> participants;   // list of players, aswell as spectators
            std::pair<int,int> players;
            int currentPlayer;             ///< Index or ID of the current player

            // !! syntax for fields is rows then collums !!

            battlespace::Grid grid1; //playfield of player 1
            battlespace::Grid grid2; //playfield of player 2



            // You can add more helper methods here as needed (e.g., checkWin, restartGame, etc.)
    };
}
