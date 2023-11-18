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
#include <QElapsedTimer>

#include <iostream>
using namespace std;

class Points
{ 
private:
    QVector<Point*> points;
    QElapsedTimer qet;
    qint64 lastTime;

    void createPoints(QVector3D center, QVector3D range, int count);

    void setupVertices();
    void setupTriangles();

    static Points* instance;

public:
    Points();
    ~Points();

    void draw();

    int pointsCount(){return points.size();}

    QVector<Point*> & getPoints() {return points;}

    void updateAll(float deltaTime);
    void update(QOpenGLShaderProgram *program);
    void paintGL(QOpenGLShaderProgram *program);

    void initBuffer(QOpenGLFunctions* context);

    static Points* Instance()
    {
        if(instance == nullptr)
        {
            instance = new Points();
            cout << "Creating new Points singleton" << endl;
        }
        return instance;
    }
};

#endif // POINTS_H
