#ifndef CELL_H
#define CELL_H

#include <QVector3D>

#define MAXNBPOINTS 1000
#define MINNBPOINTS 1

#define FRICTIONFORCE 10000
#define PRESSIONFORCE 0.00025

#define MAXUPDATECOUNT 5

#define TEMP_DIFFUSE_SPEED 100

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
        float centerDistanceRatio;

        int updateCount;

    public:
        Cell();
        Cell(int x, int y, int z, float mnbp);
        Cell(int x, int y, int z, float mnbp, float pressure, float temperature);

        void update(float deltatime);

        void deletePoint(int id,int arrayId);
        int addPoint(int id);
        void calcParams(float deltatime);
        void calcVector();

        int getMaxNbPoints(){return maxNbPoints;}
        int getNbPoints();
        int getX();
        int getY();
        int getZ();
        QVector3D getPressureVector();
        float getFriction();

        float getPressure(){return pressure;}
        float getTemp(){return temperature;}
};

#endif // CELL_H
