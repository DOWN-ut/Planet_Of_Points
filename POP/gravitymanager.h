#ifndef GRAVITYMANAGER_H
#define GRAVITYMANAGER_H

#include <QVector3D>
#include <QVector>
#include "points.h"
#include <iostream>

using namespace std;

class GravityManager
{
private:
    QVector<QVector3D> barycenters;
    static GravityManager* instance;
    const float gravityForce = 1;

public:
    GravityManager();

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
