#pragma once
#include <vector>
#include <utility>
#include <ship.hpp>
#include <set>
#include <string>
#include <array>

namespace battlespace {
    /**
    * @class Represents a Battleship grid.
    * @brief Represents the Battleship grid.
    *        o = empty   x = hit    m = miss   numbers = ship of corrosponding id
    */
    class Grid {
    public:

        /**
        * @brief Constructs a new Grid with default size 10x10.
        */
        Grid();

            /**
            * @brief Places a ship for the specified player.
            * @param shipId id of ship to be placed
            * @param pos1 starting position of placed ship this is the end closer to the top left
            * @param pos2 end of placed ship
            * @return True if the ship was placed successfully, false otherwise (e.g., overlap).
            */
        bool placeShip(int shipId,std::pair<int,int> pos1,std::pair<int,int> pos2);

        /**
        * @brief Registers a shot at the given cell.
        * @param shot std::pair<int,int> containing x then y coordinates of the shot
        * @return 0:hit 1:miss 2:out of bounds 3:repeat hit 4:hit and sink 5:error 6:winning move 7:not all ships have been placed
        */
        int shootAt(std::pair<int,int>shot);

        /**
        * @brief Prints the grid (for debugging).
        */
        void print() const;

        /**
        * @brief returns grid
        * @return grid
        */

        std::vector<std::vector<std::string>> getGrid();


         /**
        * @brief returns grid in fog of war view
        * @return grid in fog of war view
        */

        std::vector<std::vector<std::string>> getGridFogOfWar();

        /**
         * @brief returns wether all ships have been placed
         * @return true if all ships have been placed
         */

        bool getReady();

    private:
        std::vector<std::vector<std::string>> grid;
        std::set<Ship> placed;
        std::set<Ship> toPlace;

    };
}
