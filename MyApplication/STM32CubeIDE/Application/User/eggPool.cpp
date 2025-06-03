#include "EggPool.hpp"

#define POOLLIMIT 50
// Pool 10 eggs
static touchgfx::Image eggInstances[POOLLIMIT];

eggPoolManager::eggPoolManager() {
    initEggPool();
}

void eggPoolManager::initEggPool() {
    for (int i = 0; i < POOLLIMIT; ++i) {
        eggPool.enqueue(&eggInstances[i]);
    }
}

touchgfx::Image* eggPoolManager::getEggFromPool() {
    if (eggPool.isEmpty())
        return nullptr;

    touchgfx::Image* egg = nullptr;
    eggPool.dequeue(egg);
    return egg;
}

void eggPoolManager::returnEggToPool(touchgfx::Image* egg) {
    if (!egg || eggPool.isFull())
        return;

    eggPool.enqueue(egg);
}
