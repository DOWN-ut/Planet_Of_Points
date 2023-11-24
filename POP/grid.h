#ifndef GRID_H
#define GRID_H

#include "cell.h"


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
};

#endif // GRID_H
