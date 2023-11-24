#include "grid.h"

Grid::Grid()
{

}

Grid::Grid(float size,int resolution)
{
    count = resolution*resolution*resolution;
    cells = new Cell[count];
}
