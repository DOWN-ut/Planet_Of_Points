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

    int getId(int x, int y, int z)
    {
        return x + (y*resolution) + (z*resolution*resolution);
    }
    Cell getCell(int x, int y, int z)
    {
        return cells[getId(x,y,z)];
    }
    Cell getCell(QVector3D pos)
    {
        return getCell((int)pos.x(),(int)pos.y(),(int)pos.z());
    }
};

#endif // GRID_H
