#ifndef CELL_H
#define CELL_H

#include <QVector3D>
#define MAXNBPOINTS 1000
#define MINNBPOINTS 1
#define FRICTIONFORCE 10
#define PRESSIONFORCE 0.5

class Cell
{
    private:
        int x;
        int y;
        int z;

        int nbPoints; int maxNbPoints;
        int* points;//[NBPOINTS];
        float pressure;
        float temperature;
        QVector3D pressureVector;
        float friction;

    public:
        Cell();
        Cell(int x, int y, int z, float mnbp);
        Cell(int x, int y, int z, float mnbp, float pressure, float temperature);

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
