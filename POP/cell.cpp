#include "cell.h"

Cell::Cell()
{      

}

Cell::Cell(int x, int y, int z){
    this->x = x;
    this->y = y;
    this->z = z;
}

Cell::Cell(int x, int y, int z, float pressure, float temperature){
    this->x = x;
    this->y = y;
    this->z = z;

    this->pressure = pressure;
    this->temperature = temperature;
}


int Cell::getX(){
    return this->x;
}
int Cell::getY(){
    return this->y;
}
int Cell::getZ(){
    return this->z;
}
