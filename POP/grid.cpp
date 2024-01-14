#include "grid.h"
#include "glwidget.h"

Grid* Grid::instance = nullptr;

/*Grid::Grid()
{
    cout << "ininin" <<endl;
}*/

void Grid::update(float deltatime)
{
    for(int z = 0; z < resolution; z++)
    {
        for(int y = 0; y < resolution; y++)
        {
            for(int x = 0; x < resolution; x++)
            {
                cells[getId(x,y,z)]->update(deltatime);
            }
        }
    }
}

Grid::Grid(float _size,int _resolution)
{
    Grid::instance = this;

    size = _size;
    resolution = _resolution;
    count = resolution*resolution*resolution;
    cells = new Cell*[count];
    cout << "Creating grid (" << size << "  " << count << "  " << resolution << ")" << endl;

    QVector3D center = QVector3D(resolution * .5f,resolution * .5f,resolution * .5f);
    float sizeV = QVector3D(resolution,resolution,resolution).length();
    for(int z = 0; z < resolution; z++)
    {
        for(int y = 0; y < resolution; y++)
        {
            for(int x = 0; x < resolution; x++)
            {
                QVector3D d = QVector3D(x,y,z);
                float r = (d-center).length() / sizeV;
                Cell* cell = new Cell(x,y,z,r); // x y z
                cells[getId(x,y,z)] = cell;
            }
        }
    }

    cout << "  > Created grid" << endl;
}

void Grid::paintGL(QOpenGLShaderProgram *program, int mode)
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
                if(mode == 0){continue;}

                float gps = size/(float)resolution;
                glPointSize(gps * 5);//getCell(x,y,z).getDisplaySize());

                if(mode == 1)
                {
                    float cc = getCell(x,y,z)->getTemp() / getCell(x,y,z)->getMaxNbPoints(); //cout << getCell(x,y,z).getNbPoints() << endl;
                    GLWidget::setDrawColor(QVector3D(cc,0,0),cc > 0.4f ? cc : 0);//points[pIt].getColor());
                }
                else if(mode == 2)
                {
                    float cc = getCell(x,y,z)->getPressure() / 10.0f; //cout << getCell(x,y,z).getNbPoints() << endl;
                    GLWidget::setDrawColor(QVector3D(cc,0,0),cc > 0.4f ? cc : 0);//points[pIt].getColor());
                }

                glBegin(GL_POINTS);
                QVector3D v = getPosition(x,y,z);
                glVertex3f( v.x() , v.y() , v.z());
                glEnd();
            }
        }
    }

}
