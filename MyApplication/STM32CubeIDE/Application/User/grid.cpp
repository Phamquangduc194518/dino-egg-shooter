/*
 * Grid.cpp
 *
 *  Created on: May 30, 2025
 *      Author: gigab
 */

#include "grid.hpp"
grid::grid()
{
    initGrid();
    //makeRandomGrid();
}

void grid::initGrid()
{
    for (int i = 0; i < GRID_SIZE_X; i++)
    {
        for (int j = 0; j < GRID_SIZE_Y; j++)
        {
            grid_value[i][j] = 0;
        }
    }
    grid_start_x = GRID_START_X;
    grid_start_y = GRID_START_Y;
    grid_unit = GRID_UNIT;
    grid_size_x = GRID_SIZE_X;
    grid_size_y = GRID_SIZE_Y;

}

void grid::makeRandomGrid()
{
    for (int i = 0; i < GRID_SIZE_X; i++)
    {
        for (int j = 0; j < GRID_SIZE_Y; j++)
        {
            
        }
    }
}

vector2 grid::getGridFromPosition(double x, double y)
{
   int grid_x = static_cast<int>(std::round((x - grid_start_x) / grid_unit));
   int grid_y = floor((y - grid_start_y) / grid_unit);
    
    return vector2(grid_x, grid_y);
}

vector2 grid::getGridFromIndex(int index)
{
    int grid_x = index % grid_size_x;
    int grid_y = index / grid_size_x;
    return vector2(grid_x, grid_y);
}

void grid::setGridValue(vector2 position, int value)
{
    grid_value[position.x][position.y] = value;
}

int grid::getGridValue(vector2 position)
{
    return grid_value[position.x][position.y];
}

void grid::moveObjectToGridCell(Image *object, vector2 position)
{
    object->setX(position.x * grid_unit + grid_start_x);
    object->setY(position.y * grid_unit + grid_start_y);
}

void grid::moveObjectToGridCell(Image *object, int index)
{
    vector2 position = getGridFromIndex(index);
    moveObjectToGridCell(object, position);
}

int grid::getPosX(int index)
{
    return index % grid_size_x * grid_unit + grid_start_x;
}   

int grid::getPosY(int index)
{
    return index / grid_size_x * grid_unit + grid_start_y;
}

float grid::getPosX(vector2 position)
{
    return position.x * grid_unit + grid_start_x;
}

float grid::getPosY(vector2 position)
{
    return position.y * grid_unit + grid_start_y;
}








