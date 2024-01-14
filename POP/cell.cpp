#include "cell.h"
#include "points.h"
#include "grid.h"
#include "math.h"
#include <iostream>

Cell::Cell(int x, int y, int z, float rcenter): nbPoints(0)
{
    this->x = x;
    this->y = y;
    this->z = z;

    //courbe en S
    this->centerDistanceRatio = rcenter;

    float d = (MAXNBPOINTS-MINNBPOINTS) ;
    float r = (1-rcenter);
    this->maxNbPoints = MINNBPOINTS + (0.1+(((sin(r*M_PI)*pow(r,3))*d*3)));
    this->points = new int[maxNbPoints];

    this->pressure = 0;
    this->temperature = 0;
    this->updateCount = 0;

    for(int i = 0; i < maxNbPoints; i++)
    {
        this->points[i] = -1;
    }
}

Cell::Cell(int x, int y, int z, float mnbp, float pressure, float temperature) : Cell(x,y,z,mnbp)
{
    this->pressure = pressure;
    this->temperature = temperature;
}

void Cell::update(float deltatime)
{
    float val = std::rand()/(float)RAND_MAX;
    float threshold = 0.95f - (updateCount / (float)MAXUPDATECOUNT);

    if(updateCount > 0 && val > threshold)
    {
        calcParams(deltatime);
        calcVector();
        updateCount = 0;
    }
}

void Cell::deletePoint(int id, int arrayId)
{
    this->points[arrayId] = -1;
    /*
    for(unsigned long int i = 0; i < maxNbPoints; i++)
    {
        if(id == this->points[i]){
            this->points[i] = -1;
            this->nbPoints--;
            //cout << "removed point  " << i << " " << nbPoints << endl;
            updateCount++;
            break;
        }
    }*/

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
            updateCount++;
            return i;
        }
    }
    //cout << "cannot add point : " << this->nbPoints << " is over " << maxNbPoints << endl;
    return -1;
}

void Cell::calcParams(float deltatime){
    float sum = 0.0f;
    float volTot = 0.0f;
    int nbPointsInCell = 0;
    QVector<Point> points =  Points::Instance()->getPoints();

    for(int i = 0; i < maxNbPoints; i++){
        if(this->points[i] == -1) {continue;}
        sum += points[this->points[i]].getTemp();
        volTot += points[this->points[i]].getVolume();
        nbPointsInCell++;
    }

    this->pressure = (volTot);// * volTot);// / (maxNbPoints);//*maxNbPoints);//volTot > 0? this->temperature/volTot : 0;

    float targetTemp = (nbPointsInCell > 0 ? sum/nbPointsInCell : 0) * (1+(this->pressure*0.1f));
    //this->temperature += (targetTemp - this->temperature) * deltatime * TEMP_DIFFUSE_SPEED;
    this->temperature = targetTemp;

    this->friction = nbPointsInCell/(float)maxNbPoints;
    this->friction = this->friction * this->friction;
}

void Cell::calcVector(){
    QVector3D sum = QVector3D(0,0,0);
    QVector3D voisins[6];
    voisins[0] = QVector3D(-1,0,0); voisins[1] = QVector3D(1,0,0); voisins[2] = QVector3D(0,-1,0);
    voisins[3] = QVector3D(0,1,0); voisins[4] = QVector3D(0,0,-1); voisins[5] = QVector3D(0,0,1);

    float diffPresure = 0.0;


    for(int i = 0; i < 6; i++){
        Cell* neighbor = Grid::Instance()->getCell(x+voisins[i].x(), y+voisins[i].y(), z+voisins[i].z());
        if(neighbor == nullptr){
            continue;
        }
        diffPresure = this->pressure - neighbor->getPressure();
        QVector3D resultante = voisins[i] * diffPresure;
        sum += resultante;
    }
    float magn = sum.length();
    sum.normalize();
    this->pressureVector = sum * magn;// * magn;
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
    return this->friction*FRICTIONFORCE*(1-centerDistanceRatio);
}
