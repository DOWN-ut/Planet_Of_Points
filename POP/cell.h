#ifndef CELL_H
#define CELL_H

#define NBPOINTS 1000

class Cell
{
    private:
        int x;
        int y;
        int z;

        int points[NBPOINTS]{-1};
        float pressure;
        float temperature;

    public:
        Cell();
        Cell(int x, int y, int z);
        Cell(int x, int y, int z, float pressure, float temperature);

        void deletePoint(int id);
        int addPoint(int id);

        int getX();
        int getY();
        int getZ();
};

#endif // CELL_H
