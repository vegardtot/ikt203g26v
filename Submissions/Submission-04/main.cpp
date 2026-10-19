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
    delete[5] result;

    TGrid<100, 100> grid{};
    grid.Populate();
    int index = grid.FindZero<ETraversalMethod::DepthFirst>(197);
    
    grid.Print();

    std::cout << "Found zero at index: " << index << std::endl;

    return 0;
}
