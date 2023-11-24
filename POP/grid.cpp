#include "grid.h"

Grid::Grid()
{

}

Grid::Grid(float size,int resolution)
{
    instance = this;

    count = resolution*resolution*resolution;
    cells = new Cell[count];

    for(int z = 0; z < resolution; z++)
    {
        for(int y = 0; y < resolution; y++)
        {
            for(int x = 0; x < resolution; x++)
            {
                Cell cell = Cell(); // x y z
                cells[getId(x,y,z)] = cell;
            }
        }
    }
}

void Grid::paintGL(QOpenGLShaderProgram *program)
{

    for(int z = 0; z < resolution; z++)
    {
        for(int y = 0; y < resolution; y++)
        {
            for(int x = 0; x < resolution; x++)
            {
                glPointSize(5);//getCell(x,y,z).getDisplaySize());
                GLWidget::setDrawColor(QVector3D(1,1,1));//points[pIt].getColor());

                glBegin(GL_POINTS);
                QVector3D v = getPosition(x,y,z);
                glVertex3f( v.x() , v.y() , v.z());
                glEnd();
            }
        }
    }

}
