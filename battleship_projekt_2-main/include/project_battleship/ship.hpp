#pragma once


namespace battlespace{
    /**
    * @class  Represents a ship in Battleship.
    */
    class Ship {
    public:
        /**
        * @brief constcuctor of ship
        * @param int size, size of ship
        * @param if id of ship
        */

        Ship(int id, int size);
        int id;
        int size;

        bool operator<(const Ship &s)const; //compare function, so Ship can be element of set
    };
}
