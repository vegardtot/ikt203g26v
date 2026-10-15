#pragma once

#include <iostream>
#include <random>

#include "Stack.h"
#include "Queue.h"
#include <stdexcept>

enum class ETraversalMethod {
    DepthFirst,
    BreadthFirst
};

template <ETraversalMethod M, size_t size>
class TSolver {
  public:

    int AddOne(int item) {
        if constexpr (M == ETraversalMethod::DepthFirst) {
            return m_stack.Push(item);
        }
        else if constexpr (M == ETraversalMethod::BreadthFirst) {
            return m_queue.Enqueue(item);
        }
    }

    int RemoveOne() {
        if constexpr (M == ETraversalMethod::DepthFirst) {
            return m_stack.Pop();
        } else if constexpr (M == ETraversalMethod::BreadthFirst) {
            return m_queue.Dequeue();
        }
    }

    bool IsEmpty() const {
        if constexpr (M == ETraversalMethod::DepthFirst) {
            return m_stack.IsEmpty();
        } else if constexpr (M == ETraversalMethod::BreadthFirst) {
            return m_queue.IsEmpty();
        }
    }

  private:
    [[no_unique_address]] TDataStructures::TStack<size> m_stack {};
    [[no_unique_address]] TDataStructures::TQueue<size> m_queue {};
};

template<size_t columns, size_t rows>
class TGrid {

  public:

	void Print(std::ostream &os = std::cout) const {
        for (int i = 0; i < columns; ++i) {
            for (int j = 0; j < rows; ++j) {
                if (m_visited[i * rows + j]) {
                    os << "*" << m_grid[i * rows + j] << " ";
                } else {
                    os << " " << m_grid[i * rows + j] << " ";
                }
            }
            os << "\n";
        }
        os.flush();
	}

    void Populate() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distribution(0, 9);
        for (int i = 0; i < columns; ++i) {
            for (int j = 0; j < rows; ++j) {
                m_grid[i * rows + j] = distribution(gen);
            }
        }
    }

    template <ETraversalMethod method>
    int FindZero(int startIndex) {
        TSolver<method, columns * rows> solver;

        solver.AddOne(startIndex);
        while (!solver.IsEmpty()) {
            int currentIndex = solver.RemoveOne();
            if (m_grid[currentIndex] != 0) {
                m_visited[currentIndex] = true;
                int row = currentIndex / rows;
                int col = currentIndex % rows;
                // Check neighbors
                if (row > 0 && !m_visited[(row - 1) * rows + col]) { // Up
                    solver.AddOne((row - 1) * rows + col);
                }
                if (row < columns - 1 &&
                    !m_visited[(row + 1) * rows + col]) { // Down
                    solver.AddOne((row + 1) * rows + col);
                }
                if (col > 0 && !m_visited[row * rows + (col - 1)]) { // Left
                    solver.AddOne(row * rows + (col - 1));
                }
                if (col < rows - 1 &&
                    !m_visited[row * rows + (col + 1)]) { // Right
                    solver.AddOne(row * rows + (col + 1));
                }
            } else {
                m_visited[currentIndex] = true;
                return currentIndex;
            }
        }
        throw std::runtime_error("Zero not found in grid");

    }

  private:
    int m_grid[columns * rows]{};
	bool m_visited[columns * rows]{};
};