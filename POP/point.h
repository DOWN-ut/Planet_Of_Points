#ifndef POINT_H
#define POINT_H

#include <QVector3D>

class Point
{
private:
    QVector3D position;
    float mass;



public:
    Point();
    Point(QVector3D p);

    void update();
    void applyForce(QVector3D force, float deltaTime);

    QVector3D getPosition(){return position;}

};

#endif // POINT_H
