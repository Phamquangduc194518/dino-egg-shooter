#include "gameLevel.hpp"
// Define your actual level data here
static const uint8_t level0_data[77] = {
    // Fill with 77 values (e.g. 0, 1, 2 representing different tile types)
    1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
static const uint8_t level1_data[77] = {
	3, 1, 2, 0, 1, 2, 0, 1, 2, 0, 1,
	0, 2, 0, 1, 1, 2, 3, 4, 4 , 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
static const uint8_t level2_data[77] = {
    // fill another 77
};

gameLevel::gameLevel()
{
    initLevel();
}

void gameLevel::initLevel()
{
    levels[0] = level(level0_data);
    levels[1] = level(level1_data);
    levels[2] = level(level2_data);
}

const level& gameLevel::getLevel(int index) const
{
    return levels[index];
}
