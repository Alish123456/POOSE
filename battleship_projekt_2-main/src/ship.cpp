#include<ship.hpp>

namespace battlespace{


    Ship::Ship(int id, int size){
        this->size = size;
        this->id = id;
    }

    bool Ship::operator<(const Ship &s)const{
        return id<s.id;
    }

}
