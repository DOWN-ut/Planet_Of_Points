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
#include "grid.h"
#include "glwidget.h"
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
    void paintGL(QOpenGLShaderProgram *program);

    void initBuffer(QOpenGLFunctions* context);

    static Points* Instance()
    {
        //if(instance == nullptr)
        //{
        //    instance = new Points();
        //    cout << "Creating new Points singleton" << endl;
        //}
        return instance;
    }
};

#endif // POINTS_H
