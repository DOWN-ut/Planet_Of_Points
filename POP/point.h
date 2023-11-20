#ifndef POINT_H
#define POINT_H

#include <QVector3D>

class Point
{
protected:
    QVector3D position;
    float mass;

    QVector3D velocity;


public:
    Point();
    Point(QVector3D p);

    void update(float deltaTime);
    void applyForce(QVector3D force, float deltaTime);

    QVector3D getPosition(){return position;}

};

#endif // POINT_H
