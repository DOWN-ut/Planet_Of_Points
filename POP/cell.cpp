#include "cell.h"
#include "points.h"
#include "grid.h"
#include <iostream>

Cell::Cell(int x, int y, int z): nbPoints(0)
{
    this->x = x;
    this->y = y;
    this->z = z;

    this->pressure = 0;
    this->temperature = 0;

    for(int i = 0; i < NBPOINTS; i++)
    {
        this->points[i] = -1;
    }
}

Cell::Cell(int x, int y, int z, float pressure, float temperature) : Cell(x,y,z)
{
    this->pressure = pressure;
    this->temperature = temperature;;
}

void Cell::update(float deltatime)
{
    calcTemp();
    calcPressure();
    calcVector();
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
            //cout << "added point  " << this->points[i] << " at " << i << " " << this->nbPoints << endl;
            return i;
        }
    }
    cout << "cannot add point : " << this->nbPoints << " is over " << NBPOINTS << endl;
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

QVector3D Cell::calcVector(){
    QVector3D sum = QVector3D(0,0,0);
    QVector3D voisins[6];
    voisins[0] = QVector3D(-1,0,0); voisins[1] = QVector3D(1,0,0); voisins[2] = QVector3D(0,-1,0); voisins[3] = QVector3D(0,1,0); voisins[4] = QVector3D(0,0,-1); voisins[5] = QVector3D(0,0,1);

    float diffPresure = 0.0;


    for(int i = 0; i < 6; i++){
        Cell* neighbor = Grid::Instance()->getCell(x-voisins[i].x(), y-voisins[i].y(), z-voisins[i].z());
        if(neighbor == nullptr){
            continue;
        }
        diffPresure = this->pressure - neighbor->getPressure();
        QVector3D resultante = voisins[i] * diffPresure;
        sum += resultante;
    }

    return sum;
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
