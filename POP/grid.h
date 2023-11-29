#ifndef GRID_H
#define GRID_H

#include "cell.h"
#include <QVector3D>
#include <QOpenGLShaderProgram>
#include <iostream>
using namespace std;

//#include "glwidget.h"
class GLWidget;

class Grid
{
private:
    float size;
    int resolution;

    int count;
    Cell* cells = nullptr;

    static Grid* instance;

public:
    Grid();
    Grid(float size,int resolution);

    void paintGL(QOpenGLShaderProgram *program);

    bool isInside(QVector3D v)
    {
        return v.x() >= 0 && v.x() < resolution && v.y() >= 0 && v.y() < resolution && v.z() >= 0 && v.z() < resolution;
    }

    QVector3D getPosition(int x, int y, int z)
    {
        return QVector3D(
                    (-size*.5f) + (size*(x/(float)resolution)),
                    (-size*.5f) + (size*(y/(float)resolution)),
                    (-size*.5f) + (size*(z/(float)resolution))
                    );
    }
    int getId(int x, int y, int z)
    {
        return x + (y*resolution) + (z*resolution*resolution);
    }
    QVector3D cellId(QVector3D pos)
    {     
        return QVector3D(
                    (int)(((pos.x() + (size*.5f))/size)*resolution),
                    (int)(((pos.y() + (size*.5f))/size)*resolution),
                    (int)(((pos.z() + (size*.5f))/size)*resolution)
                    );
    }
    Cell getCell(int id)
    {
        return cells[id];
    }
    Cell getCell(int x, int y, int z)
    {
        return getCell(getId(x,y,z));
    }
    Cell getCell(QVector3D pos)
    {
        QVector3D v = cellId(pos);
        if(!isInside(v)){return getCell(0,0,0);}
        return getCell((int)v.x(),(int)v.y(),(int)v.z());
    }

    static Grid* Instance(){return Grid::instance;}
};

#endif // GRID_H
