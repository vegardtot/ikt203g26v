#include <iostream>
#include <string>
#include <cassert>

#include "Stack.h"
#include "Queue.h"
#include "Grid.h"

using namespace TDataStructures;

// Note: Since I defined the stack size known at compile-time as a template parameter in the
// implementation, I also need to define a suitable stack size as a template parameter
// in the function signatures.

template<size_t size> 
std::string ReverseString(const std::string &s) {
    // Make sure the stack size is sufficient to hold the string
    assert(size >= s.length());

    TStack<size> stack{};

    for (const char &c : s) {
        stack.Push(c);
    }

    std::string reversed;
    while (!stack.IsEmpty()) {
        reversed += stack.Pop();
    }

    return reversed;
}

template<size_t size>
int Factorial(int n) {
    if (n == 0) {
        return 1;
    }
    TStack<size> stack{};
    for (int i = 1; i <= n; ++i) {
        stack.Push(i);
    }
    int result = 1;
    while (!stack.IsEmpty()) {
        result *= stack.Pop();
    }
    return result;
}

template<size_t size>
static int* SimulateQueue(TQueue<size> &queue) {
    int *result = new int[size]{};
    int index = 0;

    while (!queue.IsEmpty()) {
        result[index++] = queue.Dequeue();
    }
    return result;
}

int main(int argc, char *argv[]) {
    TStack<5> stack;
    stack.Push(10);
    stack.Push(20);
    stack.Push(19);
    std::cout << "Max size: " << stack.MAX_SIZE << std::endl;
    std::cout << stack.Peek() << std::endl;

    TQueue<5> queue;
    queue.Enqueue(10);
    queue.Enqueue(20);
    queue.Enqueue(19);
    std::cout << queue.Peek() << std::endl;
    queue.Dequeue();
    std::cout << queue.Peek() << std::endl;

    const std::string input = "Hello, World!";

    std::string reversed = ReverseString<30>(input);
    std::cout << "Original: " << input << std::endl;
    std::cout << "Reversed: " << reversed << std::endl;

    int n = 5;
    int fact = Factorial<10>(n);
    std::cout << "Factorial of " << n << " is: " << fact << std::endl;

    TQueue<5> testQueue{};
    testQueue.Enqueue(1);
    testQueue.Enqueue(8);
    testQueue.Enqueue(3);
    testQueue.Enqueue(2);
    testQueue.Enqueue(23);

    int *result = SimulateQueue(testQueue);
    std::cout << "Input in order: 1 8 3 2 23\n";
    std::cout << "Output in order: ";
    for (int i = 0; i < 5; i++) {
        std::cout << result[i] << " ";
    }
    std::cout << std::endl;
    delete[] result;

    TGrid<100, 100> grid1{};
    grid1.Populate();
    int index1 = grid1.FindZero<ETraversalMethod::DepthFirst>(197);
    // LIFO guides the search to explore as far as possible along each branch
    // before backtracking. This is because the last element added to the stack
    // is the first one to be removed.  
    grid1.Print();
    std::cout << "Found zero at index: " << index1 << std::endl;

    TGrid<100, 100> grid2{};
    grid2.Populate();
    int index2 = grid2.FindZero<ETraversalMethod::BreadthFirst>(197);
    // FIFO guides the search to explore all neighbors at the present depth
    // prior to moving on to nodes at the next depth level. This is because the
    // first element added to the queue is the first one to be removed.
    grid2.Print();
    std::cout << "Found zero at index: " << index2 << std::endl;

    // Depth-first search (DFS) explores as far as possible along each branch
    // before backtracking, while breadth-first search (BFS) explores all
    // neighbors at the present depth prior to moving on to nodes at the next
    // depth level. DFS can be more memory efficient for deep trees, while BFS
    // is guaranteed to find the shortest path in unweighted graphs.
    // Both algorithms have a time complexity of O(V + E), where V is the number
    // of vertices and E is the number of edges in the graph.
    // In this case, the grid is a 2D array, and the search algorithms are used
    // to find the first occurrence of a zero in the grid. The choice between
    // DFS and BFS depends on the specific requirements of the search, such as
    // whether you want to find the first zero encountered (DFS) or the closest
    // zero in terms of distance (BFS).

    return 0;
}
