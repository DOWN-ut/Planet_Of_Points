#ifndef CELL_H
#define CELL_H

#include <QVector3D>
#define NBPOINTS 1000
#define FRICTIONFORCE 10
#define PRESSIONFORCE 0.01

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
        QVector3D pressureVector;
        float friction;

    public:
        Cell();
        Cell(int x, int y, int z);
        Cell(int x, int y, int z, float pressure, float temperature);

        void update(float deltatime);

        void deletePoint(int id);
        int addPoint(int id);
        void calcParams();
        void calcVector();

        int getNbPoints();
        int getX();
        int getY();
        int getZ();
        QVector3D getPressureVector();
        float getFriction();

        float getPressure(){return pressure;}
};

#endif // CELL_H
