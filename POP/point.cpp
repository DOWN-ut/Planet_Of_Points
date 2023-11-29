#include "point.h"
#include "grid.h"

Point::Point()
{

}

Point::Point(QVector3D p,Element e) : cellId(-1)
{
    position = p;
    element = e;
    velocity = QVector3D(0,0,0);
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
    position += velocity * deltaTime;

    temperature = 1;

    QVector3D cpos = Grid::Instance()->cellId(position);
    int cid = Grid::Instance()->getId(cpos.x(),cpos.y(),cpos.z());
    if(cellId == -1)
    {
        Grid::Instance()->getCell(cid).addPoint(id);
    }
    else if(cid != cellId)
    {
        int tempcellArrayId = Grid::Instance()->getCell(cid).addPoint(id);
        if(tempcellArrayId == -1){
            position -= velocity * deltaTime;
        }
        else{
            cellArrayId = tempcellArrayId;
            Grid::Instance()->getCell(cellId).deletePoint(id);
            cellId = cid;
        }
    }
}
