#include "cell.h"
#include "points.h"
#include "grid.h"
#include <iostream>

Cell::Cell(int x, int y, int z, float mnbp): nbPoints(0)
{
    this->x = x;
    this->y = y;
    this->z = z;

    //courbe en S
    this->maxNbPoints = MINNBPOINTS + ((MAXNBPOINTS-MINNBPOINTS) * (1-r));
    this->points = new int[maxNbPoints];

    this->pressure = 0;
    this->temperature = 0;

    for(int i = 0; i < maxNbPoints; i++)
    {
        this->points[i] = -1;
    }
}

Cell::Cell(int x, int y, int z, float mnbp, float pressure, float temperature) : Cell(x,y,z,mnbp)
{
    this->pressure = pressure;
    this->temperature = temperature;;
}

void Cell::update(float deltatime)
{
    float val = std::rand()/(float)RAND_MAX;
    int nombreAleatoire = std::rand() % 10;

    if(val > 0.9f){
        calcParams();
        calcVector();
    }
}

void Cell::deletePoint(int id){
    for(unsigned long int i = 0; i < maxNbPoints; i++){
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
    for(unsigned long int i = 0; i < maxNbPoints; i++)
    {
        if(this->points[i] == -1)
        {
            this->points[i] = id;
            this->nbPoints++;
            //cout << "added point  " << this->points[i] << " at " << i << " " << this->nbPoints << endl;
            return i;
        }
    }
    cout << "cannot add point : " << this->nbPoints << " is over " << maxNbPoints << endl;
    return -1;
}

void Cell::calcParams(){
    float sum = 0.0f;
    float volTot = 0.0f;
    int nbPointsInCell = 0;
    QVector<Point> points =  Points::Instance()->getPoints();

    for(int i = 0; i < maxNbPoints; i++){
        if(this->points[i] == -1) {continue;}
        sum += points[this->points[i]].getTemp();
        volTot += points[this->points[i]].getMass();
        nbPointsInCell++;
    }

    this->temperature = nbPointsInCell > 0? sum/nbPointsInCell : 0;
    this->pressure = volTot > 0? this->temperature/volTot : 0;
    this->friction = nbPointsInCell/(float)maxNbPoints;
    this->friction = this->friction * this->friction;
}

void Cell::calcVector(){
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
    float magn = sum.length();
    sum.normalize();
    this->pressureVector = sum * magn * magn;
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
QVector3D Cell::getPressureVector(){
    return PRESSIONFORCE*this->pressureVector;
}
float Cell::getFriction(){
    return this->friction*FRICTIONFORCE;
}
