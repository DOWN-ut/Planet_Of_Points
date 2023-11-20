#include "point.h"

Point::Point()
{

}

Point::Point(QVector3D p)
{
    position = p;
    velocity = QVector3D(0,0,0);
}

void Point::applyForce(QVector3D force, float deltaTime)
{
    velocity += deltaTime * force;
}

void Point::update(float deltaTime)
{
    position += velocity * deltaTime;
}
