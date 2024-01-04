#include "point.h"
#include "grid.h"
#include "glwidget.h"
#include "math.h"
Point::Point()
{

}

Point::Point(QVector3D p,Element e, int _id) : cellId(-1), id(_id), temperature(1)
{
    position = p;
    element = e;
    velocity = QVector3D((rand() / (float)RAND_MAX)*MAXVEL,(rand() / (float)RAND_MAX)*MAXVEL,(rand() / (float)RAND_MAX)*MAXVEL);
    mass = 1;
}

void Point::applyForce(QVector3D force, float deltaTime)
{
    velocity += deltaTime * force;
}

float Point::getMass()
{
    return this->mass;
}

float Point::getTemp()
{
    return this->temperature;
}

float Point::getVolume()
{
    return this->temperature * getSize();
}

void Point::applyFriction(float deltaTime)
{
    if(velocity.length() > 0.5f)
    {
        float v = (Grid::Instance()->getCell(cellId)->getFriction() * deltaTime);
        float val = (1 + v);
        //if(Grid::Instance()->getCell(cellId)->getFriction()>0)std::cout<<Grid::Instance()->getCell(cellId)->getFriction()<<std::endl;
        velocity /= val;
    }
}
void Point::applyPressure(float deltaTime)
{
    applyForce(Grid::Instance()->getCell(cellId)->getPressureVector() * getSize(), deltaTime);
}

void Point::drawTriangle(QVector3D p0,QVector3D p1,QVector3D p2)
{
    glVertex3f(p0.x(),p0.y(),p0.z());
    QVector3D n0 = p0 - position; n0.normalize();
    glNormal3f(n0.x(),n0.y(),n0.z());

    glVertex3f(p1.x(),p1.y(),p1.z());
    n0 = p1 - position; n0.normalize();
    glNormal3f(n0.x(),n0.y(),n0.z());

    glVertex3f(p2.x(),p2.y(),p2.z());
    n0 = p2 - position; n0.normalize();
    glNormal3f(n0.x(),n0.y(),n0.z());
}

void Point::drawSphere(float s, int slices, int stacks)
{
    QVector3D p0 = QVector3D(position.x(),position.y() + (s*0.75f),position.z());
     QVector3D p1 = QVector3D(position.x() - (s*.5f),position.y(),position.z() - (s*.5f));
     QVector3D p2 = QVector3D(position.x() + (s*.5f),position.y(),position.z() - (s*.5f));
     QVector3D p3 = QVector3D(position.x() + (s*.5f),position.y(),position.z() + (s*.5f));
     QVector3D p4 = QVector3D(position.x() - (s*.5f),position.y(),position.z() + (s*.5f));
     QVector3D p5 = QVector3D(position.x(),position.y() - (s*0.75f),position.z());

    glBegin(GL_TRIANGLES);
    drawTriangle(p0,p1,p2);
    drawTriangle(p0,p2,p3);
    drawTriangle(p0,p3,p4);
    drawTriangle(p0,p4,p1);
    drawTriangle(p5,p2,p1);
    drawTriangle(p5,p3,p2);
    drawTriangle(p5,p4,p3);
    drawTriangle(p5,p1,p4);
    glEnd();
}
void Point::draw(float baseSize)
{
    float s = getSize() * baseSize;
    glPointSize(s);
    GLWidget::setDrawColor(getColor());
    s *= 0.05f;
    drawSphere(s,5,5);
    //glBegin(GL_POINTS);
    //lVertex3f(position.x(),position.y() ,position.z());
    /*glVertex3f(position.x(),position.y() + s,position.z());
    glVertex3f(position.x(),position.y() - s,position.z());
    glVertex3f(position.x() + (s*.5f),position.y() + (s*.5f),position.z() + (s*.5f));
    glVertex3f(position.x() + (s*.5f),position.y() + (s*.5f),position.z() - (s*.5f));
    glVertex3f(position.x() - (s*.5f),position.y() - (s*.5f),position.z() + (s*.5f));
    glVertex3f(position.x() - (s*.5f),position.y() - (s*.5f),position.z() - (s*.5f));*/
    //glEnd();
}

void Point::update(float deltaTime)
{
    if(this->cellId != -1)
    {
        applyFriction(deltaTime);
        applyPressure(deltaTime);
    }
    position += velocity * deltaTime;

    temperature = 1;

    QVector3D cpos = Grid::Instance()->cellId(position);
    int cid = Grid::Instance()->getId(cpos.x(),cpos.y(),cpos.z());

    if(cid == -1)
    {
        velocity = QVector3D(0,0,0);
        position -= velocity * deltaTime;
    }
    else if(cellId == -1)
    {
        Grid::Instance()->getCell(cid)->addPoint(id);
        cellId = cid;
        cout << Grid::Instance()->getCell(cid)->getNbPoints() << endl;
    }
    else if(cid != cellId)
    {
        int tempcellArrayId = Grid::Instance()->getCell(cid)->addPoint(id);
        //cout << "Moved from  " << cellId << " to " << cid << endl;

        //cout << Grid::Instance()->getCell(cid)->getNbPoints() << endl;

        if(tempcellArrayId == -1){
            position -= velocity * deltaTime;
            velocity = -velocity;
           // cout << "Cannot mode to cell " << cid << endl;
        }
        else{
            cellArrayId = tempcellArrayId;
            Grid::Instance()->getCell(cellId)->deletePoint(id);
            cellId = cid;
        }
    }
}
