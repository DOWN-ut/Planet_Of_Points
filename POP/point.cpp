#include "point.h"

Point::Point()
{

}

Point::Point(QVector3D p)
{
    position = p;
}

void Point::applyForce(QVector3D force, float deltaTime)
{
    position += deltaTime * force;
}

void Point::update()
{

}
