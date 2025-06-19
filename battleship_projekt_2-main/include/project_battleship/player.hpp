#pragma once
#include <string>
#include <vector>
#include "Ship.hpp"
#include "Grid.hpp"

/**
 * @brief Represents a player in Battleship.
 */
class Player {
public:
    std::string name;
    Grid board;                  ///< Player's own board (with ships)
    Grid opponentView;           ///< What player knows about opponent's board
    std::vector<Ship> ships;     ///< All ships owned by player

    /**
     * @brief Constructs a player with given name.
     * @param playerName The player's name
     */
    Player(const std::string& playerName);

    /**
     * @brief Checks if all ships are sunk.
     * @return True if all ships are sunk, false otherwise.
     */
    bool hasLost() const;
};