#include "cell.h"
#include "points.h"
#include <iostream>

Cell::Cell()
{      

}

Cell::Cell(int x, int y, int z){
    this->x = x;
    this->y = y;
    this->z = z;

    this->pressure = 0;
    this->temperature = 0;
    this->nbPoints = 0;
}

Cell::Cell(int x, int y, int z, float pressure, float temperature){
    this->x = x;
    this->y = y;
    this->z = z;

    this->pressure = pressure;
    this->temperature = temperature;
    this->nbPoints = 0;
}

void Cell::deletePoint(int id){
    for(unsigned long int i = 0; i < NBPOINTS; i++){
        if(id == this->points[i]){
            this->points[i] = -1;
            this->nbPoints--;
            break;
        }
    }

    //std::cerr<<"ERROR: try to delet a point that does not exist"<<std::endl;
}

int Cell::addPoint(int id){
    for(unsigned long int i = 0; i < NBPOINTS; i++){
        if(this->points[i] == -1){
            this->points[i] = id;
            this->nbPoints++;
            return i;
        }
    }
    return -1;
}

float Cell::calcTemp(){
    float sum = 0.0f;
    int nbPointsInCell = 0;
    QVector<Point> points =  Points::Instance()->getPoints();

    for(int i = 0; i < NBPOINTS; i++){
        if(this->points[i] == -1) {continue;}
        sum += points[this->points[i]].getTemp();
        nbPointsInCell++;
    }

    this->temperature = sum/nbPointsInCell;
    return sum/nbPointsInCell;
}

float Cell::calcPressure(){
    float sum = 0.0f;
    int nbPointsInCell = 0;
    QVector<Point> points =  Points::Instance()->getPoints();

    for(int i = 0; i < NBPOINTS; i++){
        if(this->points[i] == -1) {continue;}
        sum += points[this->points[i]].getTemp();
        nbPointsInCell++;
    }

    this->temperature = sum/nbPointsInCell;
    return sum/nbPointsInCell;
}

int Cell:getNbPoints(){
    return this->nbPoints;
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
