#pragma once
#include <vector>
#include <string>
#include <optional>

enum class CellState { Empty, Ship, Hit, Miss };

struct ShipPlacement {
    int x, y;
    int length;
    bool horizontal;
};

class BattleshipGame {
public:
    BattleshipGame(int board_size = 10);

    bool place_ship(int player, const ShipPlacement& ship);
    std::optional<bool> shoot(int player, int x, int y); // returns true if hit, false if miss, nullopt if invalid
    std::string get_status() const;
    int get_current_player() const;
    int get_winner() const; // -1: none, 0 oder 1: winner

private:
    int board_size_;
    std::vector<std::vector<CellState>> boards_[2]; // two boards, one per player
    int current_player_;
    int winner_;
    // ... weitere private Felder
};