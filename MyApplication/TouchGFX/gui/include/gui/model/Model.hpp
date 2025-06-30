#ifndef MODEL_HPP
#define MODEL_HPP

class ModelListener;

class Model
{
public:
    Model();

    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }
    void setLevel(int level);
    void setTime(int time);
    void setScore(int score);
    int getLevel();
    int getTime();
    int getScore();
    void tick();
    int getHighScore() const;
private:
    int levelSelect;
    int time;
    int score;
protected:
    ModelListener* modelListener;
};

#endif // MODEL_HPP
