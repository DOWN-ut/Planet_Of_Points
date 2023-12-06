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
    cells = new Cell*[count];
    cout << "Creating grid (" << size << "  " << count << "  " << resolution << ")" << endl;

    for(int z = 0; z < resolution; z++)
    {
        for(int y = 0; y < resolution; y++)
        {
            for(int x = 0; x < resolution; x++)
            {
                Cell* cell = new Cell(x,y,z); // x y z
                cells[getId(x,y,z)] = cell;
            }
        }
    }

    cout << "  > Created grid" << endl;
}

void Grid::paintGL(QOpenGLShaderProgram *program)
{
    /*for(int i = 0; i < count ; i++)
    {
        if(cells[i]->getNbPoints() > 0){cout << "YES" << endl;}
    }*/

    for(int z = 0; z < resolution; z++)
    {
        for(int y = 0; y < resolution; y++)
        {
            for(int x = 0; x < resolution; x++)
            {
                float gps = size/(float)resolution;
                glPointSize(gps * 20);//getCell(x,y,z).getDisplaySize());

                float cc = getCell(x,y,z)->getNbPoints() / 10.0f; //cout << getCell(x,y,z).getNbPoints() << endl;

                //if(getCell(x,y,z).getNbPoints() > 0){cout << "Cell " << x << " " << y  << " " << z << " as something"<< endl;}

                GLWidget::setDrawColor(QVector3D(1,1,1),cc > 0.01f ? cc : 0);//points[pIt].getColor());

                glBegin(GL_POINTS);
                QVector3D v = getPosition(x,y,z);
                glVertex3f( v.x() , v.y() , v.z());
                glEnd();
            }
        }
    }

}
