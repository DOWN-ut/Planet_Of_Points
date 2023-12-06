#ifndef GRAVITYMANAGER_H
#define GRAVITYMANAGER_H

#include <QVector3D>
#include <QVector>
#ifndef POINTS_H
#include "points.h"
#endif
#include <iostream>
#include <vector>

using namespace std;

class GravityManager
{
private:
    QVector<QVector3D> barycenters;
    QVector3D averageSpeed;
    static GravityManager* instance;
    float gravityForce = 0.2f;

public:
    GravityManager();

    const QVector3D barycenter(int i = 0){ return barycenters.at(i);}

    void update(float deltaTime);

    void processBarycenters();
    void processAverageSpeed();

    void applyVelocity();
    void applyGravity(float deltaTime);

    static GravityManager* Instance()
    {
        if(instance == nullptr)
        {
            instance = new GravityManager();
        }
        return instance;
    }
};

#endif // GRAVITYMANAGER_H
