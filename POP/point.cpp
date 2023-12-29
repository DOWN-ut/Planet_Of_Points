#include "point.h"
#include "grid.h"

Point::Point()
{

}

Point::Point(QVector3D p,Element e, int _id) : cellId(-1), id(_id)
{
    position = p;
    element = e;
    velocity = QVector3D(0,0,0);
    mass = 1;
}

void Point::applyForce(QVector3D force, float deltaTime)
{
    velocity += deltaTime * force;
}

float Point::getMass()
{
    return this->mass;
}

float Point::getTemp()
{
    return this->temperature;
}

void Point::update(float deltaTime)
{
    if(this->cellId != -1)
    {
        applyForce(Grid::Instance()->getCell(cellId)->getPressureVector(), deltaTime);
        float val = (1 + (Grid::Instance()->getCell(cellId)->getFriction() * deltaTime));
        //if(Grid::Instance()->getCell(cellId)->getFriction()>0)std::cout<<Grid::Instance()->getCell(cellId)->getFriction()<<std::endl;
        velocity /= val;
    }
    position += velocity * deltaTime;

    temperature = 1;

    QVector3D cpos = Grid::Instance()->cellId(position);
    int cid = Grid::Instance()->getId(cpos.x(),cpos.y(),cpos.z());

    if(cid == -1)
    {
        velocity = QVector3D(0,0,0);
        position -= velocity * deltaTime;
    }
    else if(cellId == -1)
    {
        Grid::Instance()->getCell(cid)->addPoint(id);
        cellId = cid;
        cout << Grid::Instance()->getCell(cid)->getNbPoints() << endl;
    }
    else if(cid != cellId)
    {
        int tempcellArrayId = Grid::Instance()->getCell(cid)->addPoint(id);
        //cout << "Moved from  " << cellId << " to " << cid << endl;

        //cout << Grid::Instance()->getCell(cid)->getNbPoints() << endl;

        if(tempcellArrayId == -1){
            position -= velocity * deltaTime;
           // cout << "Cannot mode to cell " << cid << endl;
        }
        else{
            cellArrayId = tempcellArrayId;
            Grid::Instance()->getCell(cellId)->deletePoint(id);
            cellId = cid;
        }
    }
}
