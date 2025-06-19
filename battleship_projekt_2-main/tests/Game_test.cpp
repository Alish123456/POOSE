#include <gtest/gtest.h>
#include "game.hpp"

using namespace battlespace;

TEST(GameTest, join) {
    Game g(1);
    EXPECT_TRUE(g.join(10));//first join
    EXPECT_FALSE(g.join(10));//rejoin
    EXPECT_TRUE(g.join(11));//second join
    for (int i = 1 ; i<100 ; i++){
        EXPECT_FALSE(g.join(i));
    }
}


TEST(GameTest, startGame) {
    Game g(1);
    EXPECT_FALSE(g.startGame());//no players
    g.join(1);
    EXPECT_FALSE(g.startGame());//not enough players
    g.join(2);
    EXPECT_TRUE(g.startGame()); //started game
    EXPECT_TRUE(g.startGame()); //already active
}


TEST(GameTest, placeShip) {
    Game g(1);
    EXPECT_FALSE(g.placeShip(1,0,std::pair<int,int> (-9,0),std::pair<int,int> (0,0)));// no player
    g.join(1); //bahavious for player 1 board
    EXPECT_FALSE(g.placeShip(1,0,std::pair<int,int> (-9,0),std::pair<int,int> (0,0)));// out of bounds
    EXPECT_FALSE(g.placeShip(1,0,std::pair<int,int> (0,0),std::pair<int,int> (0,0)));// wrong length
    EXPECT_FALSE(g.placeShip(1,0,std::pair<int,int> (0,0),std::pair<int,int> (4,1)));// diagonal placement
    EXPECT_TRUE(g.placeShip(1,0,std::pair<int,int> (0,0),std::pair<int,int> (4,0)));// correct placement
    EXPECT_FALSE(g.placeShip(1,0,std::pair<int,int> (0,1),std::pair<int,int> (4,1)));// ship already placed
    EXPECT_FALSE(g.placeShip(1,4,std::pair<int,int> (1,0),std::pair<int,int> (1,1)));// overlapping ships
    EXPECT_TRUE(g.placeShip(1,1,std::pair<int,int> (0,1),std::pair<int,int> (3,1)));// correct placement
    EXPECT_TRUE(g.placeShip(1,2,std::pair<int,int> (0,2),std::pair<int,int> (2,2)));// correct placement
    EXPECT_TRUE(g.placeShip(1,3,std::pair<int,int> (0,3),std::pair<int,int> (2,3)));// correct placement
    EXPECT_TRUE(g.placeShip(1,4,std::pair<int,int> (0,4),std::pair<int,int> (1,4)));// correct placement
    EXPECT_FALSE(g.placeShip(1,4,std::pair<int,int> (0,5),std::pair<int,int> (1,5)));// all ships already placed
    g.join(2);
    g.startGame();
    EXPECT_FALSE(g.placeShip(2,0,std::pair<int,int> (-9,0),std::pair<int,int> (0,0)));// out of bounds
    EXPECT_FALSE(g.placeShip(2,0,std::pair<int,int> (0,0),std::pair<int,int> (0,0)));// wrong length
    EXPECT_FALSE(g.placeShip(2,0,std::pair<int,int> (0,0),std::pair<int,int> (4,1)));// diagonal placement
    EXPECT_TRUE(g.placeShip(2,0,std::pair<int,int> (0,0),std::pair<int,int> (4,0)));// correct placement
    EXPECT_FALSE(g.placeShip(2,0,std::pair<int,int> (0,1),std::pair<int,int> (4,1)));// ship already placed
    EXPECT_FALSE(g.placeShip(2,4,std::pair<int,int> (1,0),std::pair<int,int> (1,1)));// overlapping ships
    EXPECT_TRUE(g.placeShip(2,1,std::pair<int,int> (0,1),std::pair<int,int> (3,1)));// correct placement
    EXPECT_TRUE(g.placeShip(2,2,std::pair<int,int> (0,2),std::pair<int,int> (2,2)));// correct placement
    EXPECT_TRUE(g.placeShip(2,3,std::pair<int,int> (0,3),std::pair<int,int> (2,3)));// correct placement
    EXPECT_TRUE(g.placeShip(2,4,std::pair<int,int> (0,4),std::pair<int,int> (1,4)));// correct placement
    EXPECT_FALSE(g.placeShip(2,4,std::pair<int,int> (0,5),std::pair<int,int> (1,5)));// all ships already placed
}
