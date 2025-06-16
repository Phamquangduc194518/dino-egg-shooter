#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

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

void Model::setScore(int score)
{
    this->score = score;
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
