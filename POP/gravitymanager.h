#ifndef GRAVITYMANAGER_H
#define GRAVITYMANAGER_H

#include <QVector3D>
#include <QVector>
#ifndef POINTS_H
#include "points.h"
#endif
#include <iostream>

using namespace std;

class GravityManager
{
private:
    QVector<QVector3D> barycenters;
    static GravityManager* instance;
    float gravityForce;

public:
    GravityManager();

    const QVector3D barycenter(int i = 0){ return barycenters.at(i);}

    void update(float deltaTime);
    void processBarycenters();
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
