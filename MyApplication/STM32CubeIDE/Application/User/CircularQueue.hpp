#ifndef CIRCULAR_QUEUE_HPP
#define CIRCULAR_QUEUE_HPP

#include <cstddef>  // for size_t

template<typename T, size_t Capacity>
class CircularQueue {
public:
    CircularQueue() : head_(0), tail_(0), count_(0) {}

    bool enqueue(T item) {
        if (isFull()) return false;
        buffer_[tail_] = item;
        tail_ = (tail_ + 1) % Capacity;
        ++count_;
        return true;
    }

    bool dequeue(T& item) {
        if (isEmpty()) return false;
        item = buffer_[head_];
        buffer_[head_] = T();
        head_ = (head_ + 1) % Capacity;
        --count_;
        return true;
    }
    bool contains(T item) const {
        for (size_t i = 0; i < count_; ++i) {
            if (buffer_[(head_ + i) % Capacity] == item) {
                return true;
            }
        }
        return false;
    }   

    bool isEmpty() const { return count_ == 0; }
    bool isFull() const { return count_ == Capacity; }

private:
    T buffer_[Capacity];
    size_t head_, tail_, count_;
};

#endif // CIRCULAR_QUEUE_HPP
