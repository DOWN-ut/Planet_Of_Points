#ifndef GRID_H
#define GRID_H

#include "cell.h"
#include <QVector3D>

class Grid
{
private:
    float size;
    int resolution;
    int count;

    Cell* cells;

public:
    Grid();
    Grid(float size,int resolution);

    bool isInside(QVector3D pos)
    {
        QVector3D v = cellId(pos);
        return v.x() >= 0 && v.x() < resolution && v.y() >= 0 && v.y() < resolution && v.z() >= 0 && v.z() < resolution;
    }

    int getId(int x, int y, int z)
    {
        return x + (y*resolution) + (z*resolution*resolution);
    }
    QVector3D cellId(QVector3D pos)
    {
        return QVector3D(
                    (int)(((pos.x() + (size*.5f)/(size)))*resolution),
                    (int)(((pos.y() + (size*.5f)/(size)))*resolution),
                    (int)(((pos.z() + (size*.5f)/(size)))*resolution)
                    );
    }
    Cell getCell(int x, int y, int z)
    {
        return cells[getId(x,y,z)];
    }
    Cell getCell(QVector3D pos)
    {
        QVector3D v = cellId(pos);
        return getCell((int)v.x(),(int)v.y(),(int)v.z());
    }
};

#endif // GRID_H
