#include "point.h"

#ifndef CELL_H
#define CELL_H


class Cell
{
    private:
        int x;
        int y;
        int z;

        Point points[1000];
        float pressure;
        float temperature;

    public:
        Cell();
        Cell(int x, int y, int z);
        Cell(int x, int y, int z, float pressure, float temperature);

        int getX();
        int getY();
        int getZ();
};

#endif // CELL_H
