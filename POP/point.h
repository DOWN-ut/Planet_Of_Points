#ifndef POINT_H
#define POINT_H

#include <QVector3D>
class Grid;
class GLWidget;

#include "cell.h"

enum Element
{
    WATER,ROCK,METAL
};

class Point
{
protected:
    int id;
    int cellId;
    int cellArrayId;

    QVector3D position;
    float mass;

    QVector3D velocity;
    float temperature;

    Element element;


    QVector3D elementColors[3] = {
            QVector3D(0.,0.,1.),
            QVector3D(0.5,0.5,0.5),
            QVector3D(0.9,0.,0.)};

    float elementSizes[3] = {
            2,
            1,
            0.5
    };

public:
    Point();
    Point(QVector3D p,Element e);

    void update(float deltaTime);
    void applyForce(QVector3D force, float deltaTime);

    QVector3D getColor(){return elementColors[(int)element];}
    float getSize(){return elementSizes[(int)element] * temperature;}

    QVector3D getPosition(){return position;}
    QVector3D getVelocity(){return velocity;}

    void addVelocity(QVector3D v){velocity += v;}

};

#endif // POINT_H
