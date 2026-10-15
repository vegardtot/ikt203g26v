#pragma once

#include <stdexcept>

namespace TDataStructures {

template <int size> class TStack {
  public:
    constexpr static int MAX_SIZE = size;

  public:
    int Push(int item) {
        if (m_top >= MAX_SIZE - 1)
            throw std::runtime_error(
                "Stack overflow: Cannot push to a full stack.");

        m_data[m_top + 1] = item;
        return ++m_top;
    }

    int Pop() {
        if (m_top < 0)
            throw std::runtime_error(
                "Stack underflow: Cannot pop from an empty stack.");
        return m_data[m_top--];
    }

    int Peek() const {
        if (m_top < 0)
            throw std::runtime_error("Stack is empty: Cannot peek.");
        return m_data[m_top];
    }

    bool IsEmpty() const { return m_top < 0; }

  private:
    int m_data[MAX_SIZE]{};
    int m_top = -1;
};

} // namespace TDataStructures