#include "points.h"

Points* Points::instance = nullptr;

Points::Points()
{
    qet.start();

    createPoints(QVector3D(0,0,10),QVector3D(3,3,3),1000);
}

Points::~Points()
{

}

void Points::update(QOpenGLShaderProgram *program)
{
    float deltaTime = qet.elapsed() - lastTime;
    lastTime = qet.elapsed();

    paintGL(program);
    GravityManager::Instance()->update(deltaTime);
}

void Points::paintGL(QOpenGLShaderProgram *program)
{
    glPointSize(2);
    glColor3f(0.8,0.8,1);

    glBegin(GL_POINTS);
    for(unsigned int pIt = 0 ; pIt < points.size() ; ++pIt)
    {
        glVertex3f( points[pIt]->getPosition().x() , points[pIt]->getPosition().y(), points[pIt]->getPosition().z() );
    }
    glEnd();
}

void Points::createPoints(QVector3D center, QVector3D range, int count)
{
    for(int i = 0; i < count; i++)
    {
        float x = (((rand() / (float)RAND_MAX) * 2) - 1) * range.x();
        float y = (((rand() / (float)RAND_MAX) * 2) - 1) * range.y();
        float z = (((rand() / (float)RAND_MAX) * 2) - 1) * range.z();
        QVector3D v = QVector3D(x,y,z);
        v.normalize();

        Point* p = new Point(QVector3D(center.x() + v.x(), center.y() + v.y(), center.z() + v.z()));
        points.push_back(p);
    }
}

