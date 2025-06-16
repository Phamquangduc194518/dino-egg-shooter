#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <cstdint>

struct level
{
    uint8_t levelData[77];

    level() {}

    level(const uint8_t inputData[77])
    {
        for (int i = 0; i < 77; ++i)
        {
            levelData[i] = inputData[i];
        }
    }
};

class gameLevel
{
    level levels[3];

public:
    gameLevel();
    virtual ~gameLevel() {}
    virtual void initLevel();
    virtual const level& getLevel(int index) const;
};

#endif // LEVEL_HPP
