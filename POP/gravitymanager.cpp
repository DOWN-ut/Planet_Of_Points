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
    processAverageSpeed();
    applyVelocity();
}

void GravityManager::applyGravity(float deltaTime)
{
    QVector<Point> &points =  Points::Instance()->getPoints();

    //cout << points[0].getPosition().x() << " " << points[0].getPosition().y() << " " << points[0].getPosition().z() << " " << endl;

    for(unsigned int i = 0; i < points.size();i++)
    {
        QVector3D v = barycenters[0] - points[i].getPosition();
        float d = max(v.lengthSquared(),0.1f);
        v.normalize();
        QVector3D f = (gravityForce * v) / d;
        points[i].applyForce(f,deltaTime);
    }
}

void GravityManager::applyVelocity()
{
    QVector<Point> &points =  Points::Instance()->getPoints();

    for(unsigned int i = 0; i < points.size();i++)
    {
        points[i].addVelocity(-averageSpeed);
    }
}

void GravityManager::processAverageSpeed()
{
    averageSpeed = QVector3D(0,0,0);

    const QVector<Point> points =  Points::Instance()->getPoints();

    for(Point p : points)
    {
        averageSpeed += p.getVelocity();
    }

    averageSpeed /= points.size();
}

void GravityManager::processBarycenters()
{
    barycenters[0] = QVector3D(0,0,0);

    const QVector<Point> points =  Points::Instance()->getPoints();

    for(Point p : points)
    {
        barycenters[0] += p.getPosition();
    }

    barycenters[0] /= points.size();
}
