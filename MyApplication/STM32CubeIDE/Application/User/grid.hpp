/*
 * Grid.cpp
 *
 *  Created on: May 30, 2025
 *      Author: gigab
 */

#define GRID_SIZE_X 11
#define GRID_SIZE_Y 15
#define GRID_START_X 10
#define GRID_START_Y 10
#define GRID_UNIT 20
#define MAX_QUEUE_SIZE 64
#include <gui/common/FrontendApplication.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <cmath>
#include "Vector2.hpp"
#include "CircularQueue.hpp"

class grid
{
private:
    int grid_value[GRID_SIZE_X][GRID_SIZE_Y]; 
    bool visited[GRID_SIZE_X][GRID_SIZE_Y] = { false };
    touchgfx::Image* grid_reference[GRID_SIZE_X][GRID_SIZE_Y];
    int grid_start_x;
    int grid_start_y;
    int grid_unit;      
    int grid_size_x;
    int grid_size_y;    

public:
    grid();
    virtual ~grid(){}
    virtual vector2 getGridFromPosition(double x, double y);
    virtual void setGridValue(vector2 position, int value);
    virtual void setGridReference(vector2 position, touchgfx::Image* value);
    virtual int getGridValue(vector2 position);
    virtual touchgfx::Image* getGridReference(vector2 position);
    virtual float getPosX(vector2 gridPos);
    virtual float getPosY(vector2 gridPos);
    uint8_t floodFill(uint8_t startRow, uint8_t startCol, vector2 output[], uint8_t maxOutput);

private:
    void initGrid();
    void makeRandomGrid();
};



