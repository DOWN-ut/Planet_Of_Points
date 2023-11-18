#include "gravitymanager.h"

GravityManager* GravityManager::instance = nullptr;

GravityManager::GravityManager()
{
    barycenters.resize(1);
    gravityForce = 0.01;
}

void GravityManager::update(float deltaTime)
{
    processBarycenters();
    applyGravity(deltaTime);
}

void GravityManager::applyGravity(float deltaTime)
{
    QVector<Point*> &points =  Points::Instance()->getPoints();

    cout << points[0]->getPosition().x() << " " << points[0]->getPosition().y() << " " << points[0]->getPosition().z() << " " << endl;

    for(Point* p : points)
    {
        QVector3D v = barycenters[0] - p->getPosition();
        v.normalize();
        QVector3D f = gravityForce * v;
        p->applyForce(f,deltaTime);
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
