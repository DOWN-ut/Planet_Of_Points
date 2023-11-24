#include "grid.h"
#include "glwidget.h"

Grid* Grid::instance = nullptr;

Grid::Grid()
{

}

Grid::Grid(float _size,int _resolution)
{
    Grid::instance = this;

    cout << "Creating grid" << endl;

    size = _size;
    resolution = _resolution;
    count = resolution*resolution*resolution;
    cells = new Cell[count];
    cout << count << "  " << resolution << endl;

    for(int z = 0; z < resolution; z++)
    {
        for(int y = 0; y < resolution; y++)
        {
            for(int x = 0; x < resolution; x++)
            {
                Cell cell = Cell(x,y,z); // x y z
                cells[getId(x,y,z)] = cell;
            }
        }
    }

    cout << "Created grid" << endl;
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
