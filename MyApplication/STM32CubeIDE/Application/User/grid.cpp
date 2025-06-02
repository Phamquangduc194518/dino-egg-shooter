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
    int grid_y = static_cast<int>(std::round((y - grid_start_y) / grid_unit));
    if(grid_x<0)
    {
        grid_x = -1;
    }
    else if(grid_x>=grid_size_x)
    {
        grid_x = grid_size_x;
    }
    if(grid_y<0)
    {
        grid_y = -1;
    }
    else if(grid_y>=grid_size_y)
    {
        grid_y = grid_size_y;
    }
    return vector2(grid_x, grid_y);
}


void grid::setGridValue(vector2 position, int value)
{
    grid_value[position.x][position.y] = value;
}

int grid::getGridValue(vector2 position)
{
    if(position.x < 0 || position.x >= grid_size_x || position.y < 0 || position.y >= grid_size_y)
    {
        return 0;
    }
    else
    {
        return grid_value[position.x][position.y];
    }
}

float grid::getPosX(vector2 position)
{
    if(position.x < 0)
    {
        return grid_start_x;
    }
    else if(position.x > grid_size_x)
    {
        return grid_size_x;
    }
    else
    {
        return position.x * grid_unit + grid_start_x;
    }
}

float grid::getPosY(vector2 position)
{
    if(position.y < 0)
    {
        return grid_start_y;
    }
    else
    {
        return position.y * grid_unit + grid_start_y;
    }
}








