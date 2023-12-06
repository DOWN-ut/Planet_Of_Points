#ifndef POINTS_H
#define POINTS_H

#include "gravitymanager.h"

#include <QVector3D>
#include <qopengl.h>
#include <QVector>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>

#include "point.h"

class Grid;
class GLWidget;

#include <QElapsedTimer>
#include <vector>

#include <iostream>
using namespace std;

class Points
{ 
private:
    QVector<Point> points;

    void createPoints(QVector3D center, QVector3D rangeMin, QVector3D rangeMax, int count);

    void setupVertices();
    void setupTriangles();

    const float baseSize = 2;

    static Points* instance;

public:
    Points();
    ~Points();

    void draw();

    int pointsCount(){return points.size();}

    QVector<Point> & getPoints() {return points;}

    void initGL(QOpenGLShaderProgram *program);

    void update(float deltaTime);
    void paintGL(QOpenGLShaderProgram *program,int mode);

    void initBuffer(QOpenGLFunctions* context);

    static Points* Instance()
    {
        return instance;
    }
};

#endif // POINTS_H
