#ifndef EGGPOOL_HPP
#define EGGPOOL_HPP

#define POOLLIMIT 25
#include <touchgfx/widgets/Image.hpp>
#include "CircularQueue.hpp"
class eggPoolManager
{
    private:
    public:
    CircularQueue<touchgfx::Image*, POOLLIMIT> eggPool;
    eggPoolManager();
    void initEggPool();
    touchgfx::Image* getEggFromPool();
    void returnEggToPool(touchgfx::Image* egg);
};
#endif // EGGPOOL_HPP
