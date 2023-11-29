#include "grid.h"
#include "glwidget.h"

Grid* Grid::instance = nullptr;

/*Grid::Grid()
{
    cout << "ininin" <<endl;
}*/

Grid::Grid(float _size,int _resolution)
{
    Grid::instance = this;

    size = _size;
    resolution = _resolution;
    count = resolution*resolution*resolution;
    cells = new Cell[count];
    cout << "Creating grid (" << size << "  " << count << "  " << resolution << ")" << endl;

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

    cout << "  > Created grid" << endl;
}

void Grid::paintGL(QOpenGLShaderProgram *program)
{
    for(int z = 0; z < resolution; z++)
    {
        for(int y = 0; y < resolution; y++)
        {
            for(int x = 0; x < resolution; x++)
            {
                float gps = size/(float)resolution;
                glPointSize(gps * 10);//getCell(x,y,z).getDisplaySize());

                float cc = getCell(x,y,z).getNbPoints() / 100f;
                GLWidget::setDrawColor(QVector3D(1,1-cc,1-cc));//points[pIt].getColor());

                glBegin(GL_POINTS);
                QVector3D v = getPosition(x,y,z);
                glVertex3f( v.x() , v.y() , v.z());
                glEnd();
            }
        }
    }

}
