#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>
#include "FlashStorage.h"

Model::Model() : modelListener(0)
{

}

void Model::tick()
{

}

void Model::setLevel(int level)
{
    levelSelect = level;
}

void Model::setTime(int time)
{
    this->time = time;
}       

void Model::setScore(int newScore)
{
    score = newScore;
    uint32_t savedHigh = Flash_ReadHighScore();
    if (newScore > (int)savedHigh)
    {
        Flash_WriteHighScore(newScore);
    }
}

int Model::getLevel()
{
    return levelSelect;
}

int Model::getTime()
{
    return time;
}

int Model::getScore()
{
    return score;
}

int Model::getHighScore() const
{
    return Flash_ReadHighScore();
}
