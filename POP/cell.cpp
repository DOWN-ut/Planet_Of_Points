#include "cell.h"
#include "points.h"
#include <iostream>

Cell::Cell()
{      

}

Cell::Cell(int x, int y, int z): nbPoints(0)
{
    this->x = x;
    this->y = y;
    this->z = z;

    this->pressure = 0;
    this->temperature = 0;
}

Cell::Cell(int x, int y, int z, float pressure, float temperature) : nbPoints(0)
{
    this->x = x;
    this->y = y;
    this->z = z;

    this->pressure = pressure;
    this->temperature = temperature;;
}

void Cell::deletePoint(int id){
    for(unsigned long int i = 0; i < NBPOINTS; i++){
        if(id == this->points[i]){
            this->points[i] = -1;
            this->nbPoints--;
            //cout << "removed point  " << i << " " << nbPoints << endl;
            break;
        }
    }

    //std::cerr<<"ERROR: try to delet a point that does not exist"<<std::endl;
}

int Cell::addPoint(int id){
    for(unsigned long int i = 0; i < NBPOINTS; i++)
    {
        if(this->points[i] == -1)
        {
            this->points[i] = id;
            this->nbPoints++;
            cout << "added point  " << this->points[i] << " at " << i << " " << this->nbPoints << endl;
            return i;
        }
    }
    return -1;
}

float Cell::calcPressure(){
    float volTot = 0.0f;
    float temp = calcTemp();
    QVector<Point> points =  Points::Instance()->getPoints();

    for(int i = 0; i < NBPOINTS; i++){
        if(this->points[i] == -1) {continue;}
        volTot += points[this->points[i]].getMass();
    }

    this->pressure = temp/volTot;
    return temp/volTot;
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

int Cell::getNbPoints(){
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
