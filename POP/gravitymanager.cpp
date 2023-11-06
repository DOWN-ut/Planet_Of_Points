#include "gravitymanager.h"

GravityManager* GravityManager::instance = nullptr;

GravityManager::GravityManager()
{
    barycenters.resize(1);
}

void GravityManager::update(float deltaTime)
{
    processBarycenters();
    applyGravity(deltaTime);
    cout << deltaTime << endl;
}

void GravityManager::applyGravity(float deltaTime)
{
    const QVector<Point*> points =  Points::Instance()->getPoints();

    for(Point* p : points)
    {
        QVector3D v = barycenters[0] - p->getPosition();
        v.normalize();
        p->applyForce(v*gravityForce,deltaTime);
    }
}

void GravityManager::processBarycenters()
{
    barycenters[0] = QVector3D(0,0,0);

    const QVector<Point*> points =  Points::Instance()->getPoints();

    for(Point* p : points)
    {
        barycenters[0] += p->getPosition();
    }

    barycenters[0] /= points.size();
}
