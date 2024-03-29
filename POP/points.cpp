#include "points.h"
#include "glwidget.h"
#include "grid.h"

Points* Points::instance = nullptr;

Points::Points()
{
    initPoints();
    Points::instance = this;
}

void Points::initPoints()
{
    int _c = 5000;

    cout << "Creating " << _c << " points" << endl;
    createPoints(QVector3D(0,0,0),QVector3D(5,5,5),QVector3D(7,7,7),_c);
    cout << " >> Succesfull" << endl;
}

Points::~Points()
{

}

void Points::update(float deltaTime)
{
    GravityManager::Instance()->update(deltaTime);
    for(unsigned int pIt = 0 ; pIt < points.size() ; ++pIt)
    {
        points[pIt].update(deltaTime);
    }
}

void Points::initGL(QOpenGLShaderProgram *program)
{
    for(Point p : points)
    {
        p.initGL();
    }
}

void Points::paintGL(QOpenGLShaderProgram *program,int mode, int particlesDisplayAttributs)
{

    for(unsigned int pIt = 0 ; pIt < points.size() ; ++pIt)
    {
        if(mode != 0 && mode-1 != (int)points[pIt].getElement()){continue;}
        points[pIt].draw(program,baseSize,particlesDisplayAttributs);
     }


    glPointSize(10);

    GLWidget::setDrawColor(QVector3D(1, 1, 0));

    glBegin(GL_POINTS);
    QVector3D p = GravityManager::Instance()->barycenter();
    glVertex3f( p.x() , p.y(), p.z() );
    glEnd();
}

void Points::createPoints(QVector3D center, QVector3D rangeMin, QVector3D rangeMax, int count)
{
    srand(time(NULL));
    for(int i = 0; i < count; i++)
    {
        float x = (((rand() / (float)RAND_MAX) * 2) - 1) ;
        float y = (((rand() / (float)RAND_MAX) * 2) - 1);
        float z = (((rand() / (float)RAND_MAX) * 2) - 1) ;
        QVector3D v = QVector3D(x,y,z);
        v.normalize();

        QVector3D randV = QVector3D(
                    rangeMin.x() + ((rangeMax.x() - rangeMin.x()) * (rand() / (float)RAND_MAX)),
                    rangeMin.y() + ((rangeMax.y() - rangeMin.y()) * (rand() / (float)RAND_MAX)),
                    rangeMin.z() + ((rangeMax.z() - rangeMin.z()) * (rand() / (float)RAND_MAX)));
        v = QVector3D(v.x() * randV.x(),v.y() * randV.y(),v.z() * randV.z());

        QVector3D pos = QVector3D(center.x() + v.x(), center.y() + v.y(), center.z() + v.z());
        Element e = (Element)(int)((rand() / (float)RAND_MAX) * 3);
        Point p = Point(pos,e,i);

        points.push_back(p);
    }

}
