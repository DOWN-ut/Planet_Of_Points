#include "cell.h"
#include <iostream>

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

void Cell::deletePoint(int id){
    for(unsigned long int i = 0; i < NBPOINTS; i++){
        if(id == this->points[i]){
            this->points[i] = -1;
            break;
        }
    }

    std::cerr<<"ERROR: try to delet a point that does not exist"<<std::endl;
}

int Cell::addPoint(int id){
    for(unsigned long int i = 0; i < NBPOINTS; i++){
        if(id == -1){
            this->points[i] = id;
            return i;
        }
    }
    return -1;
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
