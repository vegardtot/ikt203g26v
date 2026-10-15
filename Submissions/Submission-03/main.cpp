#include <iostream>
#include <string>

// Time complexity: O(n)
// Space complexity: O(n)
static void printNaturalNumbers(int n) {
    if (n == 1) {
        std::cout << 1 << std::endl;
        return;     
    }
    printNaturalNumbers(n - 1);
    std::cout << n << std::endl;
}

// Time complexity: O(n)
// Space complexity: O(n)
static int calculateFactorial(int n) {
    if (n == 0 || n == 1)
        return 1;
    return n * calculateFactorial(n - 1);
}

// Time complexity: O(n)
// Space complexity: O(n)
// Where n is the exponent
static int power(int base, int exponent) {
    if (exponent == 0)
        return 1;
    return base * power(base, exponent - 1);
}

// Time complexity: O(log n)
// Space complexity: O(log n)
static int powerImproved(int base, int exponent) {
    if (exponent == 0)
        return 1;
    if (exponent % 2 == 0) {
        int halfPower = powerImproved(base, exponent / 2);
        return halfPower * halfPower;
    }
    return base * powerImproved(base, exponent - 1);
}

// Time complexity: O(2^n)
// Space complexity: O(n)
// Note: This is a naive recursive implementation of Fibonacci and is not
// efficient for large n. The same parameters are recalculated multiple times. For
// large n, consider using caching or a non-recursive approach.
static int fibonacci(int n) {
    if (n <= 1)
        return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

// Time complexity: O(n)
// Space complexity: O(n)
static int countOccurrences(const std::string& s, char c) {
    if (s.empty())
        return 0;
    int count = (s[0] == c) ? 1 : 0;
    return count + countOccurrences(s.substr(1), c);
}

// Time complexity: O(n)
// Space complexity: O(log n)
static int findLargestElement(const int arr[], int size) {
    if (size == 1)
        return arr[0];

    const int leftSize = size / 2;
    const int* rightSide = &arr[leftSize];

    int maxLeft = findLargestElement(arr, leftSize);
    int maxRight = findLargestElement(rightSide, size - leftSize);
    return maxLeft > maxRight ? maxLeft : maxRight;
}

// Time complexity: O(n)
// Space complexity: O(n)
// Note: Printing before and after the recursive call will print the characters
// in ascending order first, and then in descending order. This is because the
// recursive call goes deeper before printing the next character, and then
// prints the characters on the way back up the call stack.
static void traverseAsciiTable(char start, char end) {
    if (start > end)
        return;
    std::cout << start << std::endl;
    traverseAsciiTable(start + 1, end);
    std::cout << start << std::endl;
}


int main (int argc, char *argv[]) {
    printNaturalNumbers(5);
    std::cout << "Factorial of 5: " << calculateFactorial(5) << std::endl;
    std::cout << "2 raised to the power of 3: " << power(2, 3) << std::endl;
    std::cout << "3 raised to the power of 3 (improved): " << powerImproved(3, 3) << std::endl;
    std::cout << "Fibonacci of 5: " << fibonacci(5) << std::endl;
    std::string testString = "hello world";
    char testChar = 'o';
    std::cout << "Occurrences of '" << testChar << "' in \"" << testString
              << "\": " << countOccurrences(testString, testChar) << std::endl;
    const int arr[] = {1, 3, 5, 7, 9};
    int size = sizeof(arr) / sizeof(arr[0]);
    std::cout << "Largest element in the array: "
              << findLargestElement(arr, size) << std::endl;
    std::cout << "Traversing ASCII table from 'A' to 'Z':" << std::endl;
    traverseAsciiTable('A', 'Z');
    return 0;
}
