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
    max_valued_y =1;
    currentVisited =0;
    maxVisited =0;

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

    if(position.y>=max_valued_y)
        max_valued_y =position.y+1;
    maxVisited+= (value!=0) ? 1 : -1 ;
}

int grid::getGridValue(vector2 position)
{
    if(position.x < 0 || position.x >= grid_size_x || position.y < 0 || position.y >= max_valued_y)
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



void grid::setGridReference(vector2 position, touchgfx::Image* value)
{
    grid_reference[position.x][position.y] = value;
}

touchgfx::Image* grid::getGridReference(vector2 position)
{
    return grid_reference[position.x][position.y];
}

bool grid::hasMemberWithYZero(vector2 positions[], uint8_t count) {
    for (uint8_t i = 0; i < count; i++) {
        if (positions[i].y == 0) {
            return true;
        }
    }
    return false;
}

uint8_t grid::floodFill(uint8_t startRow, uint8_t startCol, vector2 output[], uint8_t maxOutput)
{
	resetVisit();
    uint8_t targetValue = grid_value[startRow][startCol];
    uint8_t found = 0;
    CircularQueue<vector2, MAX_QUEUE_SIZE> queue;
    visited[startRow][startCol] = true;
    queue.enqueue(vector2(startRow, startCol));
    const int8_t dx[4] = {-1, 1, 0, 0};
    const int8_t dy[4] = {0, 0, -1, 1};

    while (!queue.isEmpty())    
    {
        vector2 current(0,0);
        queue.dequeue(current);
        int x = current.x;
        int y = current.y;
        if(found < maxOutput)
        {
            output[found++] = current;
        }
        for(int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if(nx >= 0 && nx < GRID_SIZE_X && ny >= 0 && ny < GRID_SIZE_Y && !visited[nx][ny] && grid_value[nx][ny] == targetValue)
            {
                visited[nx][ny] = true;
                queue.enqueue(vector2(nx, ny));
            }
        }
    }
    return found;
}

uint8_t grid::floodFillNoDiff(uint8_t startRow, uint8_t startCol, vector2 output[], uint8_t maxOutput)
{
    uint8_t found = 0;
    CircularQueue<vector2, MAX_QUEUE_SIZE> queue;
    visited[startRow][startCol] = true;
    currentVisited+=1;
    queue.enqueue(vector2(startRow, startCol));
    const int8_t dx[4] = {-1, 1, 0, 0};
    const int8_t dy[4] = {0, 0, -1, 1};

    while (!queue.isEmpty())
    {
        vector2 current(0,0);
        queue.dequeue(current);
        int x = current.x;
        int y = current.y;
        if(found < maxOutput)
        {
            output[found++] = current;
        }
        for(int i = 0; i < 4; i++)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if(nx >= 0 && nx < GRID_SIZE_X && ny >= 0 && ny < GRID_SIZE_Y && !visited[nx][ny] && grid_value[nx][ny] >0 )
            {
                visited[nx][ny] = true;
                currentVisited+=1;
                queue.enqueue(vector2(nx, ny));
            }
        }
    }
    return found;
}
void grid:: resetVisit()
{
	currentVisited =0;
	for (int i = 0; i < GRID_SIZE_X; ++i)
		for (int j = 0; j < max_valued_y; ++j)
			visited[i][j] = false;
}

uint8_t grid::findIsolatedGroupsWithoutYZero(vector2 outputGroups[MAX_QUEUE_SIZE])
{
    // Reset visited array
    vector2 tempGroup[MAX_QUEUE_SIZE];
    if(currentVisited == maxVisited)
    	doneVisit = true;
    // Scan the entire grid
    for (int i = 0; i < GRID_SIZE_X ; i++)
    {
        for (int j = 0; j < max_valued_y ; j++)
        {
            // If this cell hasn't been visited and has a non-zero value
            if (!visited[i][j] && grid_value[i][j] != 0)
            {
                // Find the group starting from this cell
                uint8_t groupSize = floodFillNoDiff(i, j, tempGroup, MAX_QUEUE_SIZE);
                
                // Check if the group has any members with y=0
                if (!hasMemberWithYZero(tempGroup, groupSize))
                {
                    for(int k = 0; k < groupSize; k++)
                    {
                        outputGroups[k] = tempGroup[k];
                    }
                    return groupSize;
                }
            }
        }
    }
    return 0;
}

