#include <grid.hpp>
#include <iostream>

int main() {
    battlespace::Grid grid;
    grid.placeShip(0,std::pair<int,int>(0,0),std::pair<int,int>(0,4));
    grid.print();

    return 0;
}
