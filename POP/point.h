#ifndef POINT_H
#define POINT_H

#include <QVector3D>
class Grid;
class GLWidget;

#include "cell.h"
#include <GL/glut.h>

enum Element
{
    WATER,ROCK,METAL
};

#define MAXVEL 0.2

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

    void applyFriction(float deltaTime);
    void applyPressure(float deltaTime);

public:
    Point();
    Point(QVector3D p,Element e, int _id);

    void update(float deltaTime);
    void applyForce(QVector3D force, float deltaTime);

    Element getElement(){return element;}
    QVector3D getColor(){return elementColors[(int)element];}
    float getSize(){return elementSizes[(int)element] * temperature;}

    QVector3D getPosition(){return position;}
    QVector3D getVelocity(){return velocity;}

    void addVelocity(QVector3D v){velocity += v;}

    void drawTriangle(QVector3D p0,QVector3D p1,QVector3D p2);
    void drawSphere(float r, int slices, int stacks);
    void draw(float baseSize);

    float getMass();
    float getTemp();
    float getVolume();

};

#endif // POINT_H
