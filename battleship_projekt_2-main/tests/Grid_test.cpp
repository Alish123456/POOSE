#include <gtest/gtest.h>
#include "grid.hpp"

using namespace battlespace;


/**
        toPlace.insert(battlespace::Ship(0,5));
        toPlace.insert(battlespace::Ship(1,4));
        toPlace.insert(battlespace::Ship(2,3));
        toPlace.insert(battlespace::Ship(3,3));
        toPlace.insert(battlespace::Ship(4,2));
        */
TEST(GridTest, placeShip) {
    Grid g;
    EXPECT_FALSE(g.placeShip(0,std::pair<int,int> (-9,0),std::pair<int,int> (0,0)));// out of bounds
    EXPECT_FALSE(g.placeShip(0,std::pair<int,int> (0,0),std::pair<int,int> (0,0)));// wrong length
    EXPECT_FALSE(g.placeShip(0,std::pair<int,int> (0,0),std::pair<int,int> (4,1)));// diagonal placement
    EXPECT_TRUE(g.placeShip(0,std::pair<int,int> (0,0),std::pair<int,int> (4,0)));// correct placement
    EXPECT_FALSE(g.placeShip(0,std::pair<int,int> (0,1),std::pair<int,int> (4,1)));// ship already placed
    EXPECT_FALSE(g.placeShip(4,std::pair<int,int> (1,0),std::pair<int,int> (1,1)));// overlapping ships
    EXPECT_TRUE(g.placeShip(1,std::pair<int,int> (0,1),std::pair<int,int> (3,1)));// correct placement
    EXPECT_TRUE(g.placeShip(2,std::pair<int,int> (0,2),std::pair<int,int> (2,2)));// correct placement
    EXPECT_TRUE(g.placeShip(3,std::pair<int,int> (0,3),std::pair<int,int> (2,3)));// correct placement
    EXPECT_TRUE(g.placeShip(4,std::pair<int,int> (0,4),std::pair<int,int> (1,4)));// correct placement
    EXPECT_FALSE(g.placeShip(4,std::pair<int,int> (0,5),std::pair<int,int> (1,5)));// all ships already placed
}
 //@return 0:hit 1:miss 2:out of bounds 3:repeat hit 4:hit and sink  5:error 6:winning shot
TEST(GridTest, shootAt) {
     Grid g;
     g.placeShip(0,std::pair<int,int> (0,0),std::pair<int,int> (4,0));
     g.placeShip(4,std::pair<int,int> (0,1),std::pair<int,int> (1,1));
     EXPECT_EQ(g.shootAt(std::pair<int,int> (0,0)),0); //hit ship
     EXPECT_EQ(g.shootAt(std::pair<int,int> (0,0)),3); //repeat hit
     EXPECT_EQ(g.shootAt(std::pair<int,int> (0,2)),1); //miss
     EXPECT_EQ(g.shootAt(std::pair<int,int> (0,2)),3); //repeat hit
     EXPECT_EQ(g.shootAt(std::pair<int,int> (0,-1)),2); //out of bounds
     EXPECT_EQ(g.shootAt(std::pair<int,int> (1,0)),0); //hit ship
     EXPECT_EQ(g.shootAt(std::pair<int,int> (2,0)),0); //hit ship
     EXPECT_EQ(g.shootAt(std::pair<int,int> (3,0)),0); //hit ship
     EXPECT_EQ(g.shootAt(std::pair<int,int> (4,0)),4); //hit and sink ship
     EXPECT_EQ(g.shootAt(std::pair<int,int> (0,1)),0); //hit ship
     EXPECT_EQ(g.shootAt(std::pair<int,int> (1,1)),6); //winning shot
     // return value 5 shouldnt be possible to reach
}
TEST(GridTeast, getReady) {
    Grid g;
    EXPECT_FALSE(g.getReady()); // not all ships have been placed yet
    g.placeShip(0,std::pair<int,int> (0,0),std::pair<int,int> (4,0));// correct placement
    EXPECT_FALSE(g.getReady()); // not all ships have been placed yet
    g.placeShip(1,std::pair<int,int> (0,1),std::pair<int,int> (3,1));// correct placement
    EXPECT_FALSE(g.getReady()); // not all ships have been placed yet
    g.placeShip(2,std::pair<int,int> (0,2),std::pair<int,int> (2,2));// correct placement
    EXPECT_FALSE(g.getReady()); // not all ships have been placed yet
    g.placeShip(3,std::pair<int,int> (0,3),std::pair<int,int> (2,3));// correct placement
    EXPECT_FALSE(g.getReady()); // not all ships have been placed yet
    g.placeShip(4,std::pair<int,int> (0,4),std::pair<int,int> (1,4));// correct placement
    EXPECT_TRUE(g.getReady()); // all ships placed
}





