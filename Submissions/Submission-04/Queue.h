#pragma once

#include <stdexcept>

namespace TDataStructures {

template <int size>
class TQueue {
  public:
    constexpr static int MAX_SIZE = size;

  public:
    int Enqueue(int item) {
        if (m_count >= MAX_SIZE)
            throw std::runtime_error(
                "Queue overflow: Cannot enqueue to a full queue.");
        ++m_back %= MAX_SIZE;
        m_data[m_back] = item;
        if (++m_count == 1)
            m_front = m_back;
        return 0;
    }

    int Dequeue() {
        if (m_count <= 0)
            throw std::runtime_error(
                "Queue underflow: Cannot dequeue from an empty queue.");
        int item = m_data[m_front];
        ++m_front %= MAX_SIZE;
        --m_count;
        return item;
    }

    int Peek() const {
        if (m_count <= 0)
            throw std::runtime_error("Queue is empty: Cannot peek.");
        return m_data[m_front];
    }

    bool IsEmpty() const { return m_count <= 0; }

  private:
    int m_data[MAX_SIZE]{};
    int m_front = -1;
    int m_back = -1;
    int m_count = 0;
	
};
} // namespace TDataStructures