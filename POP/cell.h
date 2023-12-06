#ifndef CELL_H
#define CELL_H

#include <QVector3D>
#define NBPOINTS 1000

class Cell
{
    private:
        int x;
        int y;
        int z;

        int nbPoints;
        int points[NBPOINTS];
        float pressure;
        float temperature;

    public:
        Cell();
        Cell(int x, int y, int z);
        Cell(int x, int y, int z, float pressure, float temperature);

        void update(float deltatime);

        void deletePoint(int id);
        int addPoint(int id);
        float calcTemp();
        float calcPressure();
        QVector3D calcVector();

        int getNbPoints();
        int getX();
        int getY();
        int getZ();

        float getPressure(){return pressure;}
};

#endif // CELL_H
