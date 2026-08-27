#include <iostream>
#include <string>
#include <cstdlib>

#include "template.h"

////////////////////////////////////////////////////////////////////////////////////
/// Step 1
////////////////////////////////////////////////////////////////////////////////////


// Disable automatic padding for the purpose to see
// that the sizeof TMyStruct is the sum of the fields
#pragma pack(push, 1)
struct TMyStruct {
    double foo;
    int bar;
};
#pragma pack(pop)

struct TStudent {
    unsigned int grade;
    bool operator>(const TStudent &other) const { return grade > other.grade; }
};

////////////////////////////////////////////////////////////////////////////////////
/// Step 2
////////////////////////////////////////////////////////////////////////////////////

static int Add(int a, int b) {
    return a + b;
}

static std::string Greet(const std::string& name) {
    return std::string("Hello ") + name;
}

using GreetPtr = std::string (*)(const std::string&);

static bool IsEven(int a) { return a % 2 == 0; }

static bool IsOdd(int a) { return a % 2 == 1; }

static void FilterAndPrint(const int* ptr, unsigned int len, bool (*filter)(int)) {
    for (unsigned int i = 0; i < len; i++) {
        if (filter(*(ptr + i)))
            std::cout << *(ptr + i) << ' ';
    } std::cout << std::endl;
}

static void Play() {
    std::cout << "Playing game...\n";
}

static void Pause() {
    std::cout << "Game paused.\n";
}

static void Quit() {
    std::cout << "Quitting game.\n";
}

static void DoubleInt(int &a) { a*= 2;}


// ASCII A - 0b01000001
// ASCII a - 0b01100001
// Subtract: 0b00100000
static void CapitalizeChar(char &c) { c -= 0b00100000; }

int main() {


    // Step 1.1.a
    constexpr int a = 3;
    constexpr double b = 3.1;

    PrintTypeSize(a);
    PrintTypeSize(b);
    PrintTypeSize(TMyStruct{
        .foo = b,
        .bar = a,
    });

    // Step 1.1.b
    std::cout << "Max(1, 5) = " << GetMax(1, 5) << std::endl;

    // Step 1.1.c
    constexpr TStudent s1 = {.grade = 3};
    constexpr TStudent s2 = {.grade = 5};

    std::cout << "Max(s1, s2) = " << GetMax(s1, s2).grade << std::endl;

    // Step 1.2.a
    const auto mytype = TDataPack<int, float, double, char>{};
    
    // Step 1.2.b
    auto cls = TStaticArray<int, 5>{};
    cls.Append(3);
    cls.Append(6);
    cls.Append(9);
    cls.PrintItems();

    auto stringcls = TStaticArray<const char*, 10>{};
    stringcls.Append("Hello,");
    stringcls.Append("World!");

    // Step 1.2.c
    auto wrapper = PrintContainer<TStaticArray, const char*, 10>;
    wrapper(stringcls);

    // Step 2.1.a
    int (*add)(int, int) = &Add;
    
    // Explicit dereference
    (*add)(2, 3);

    // Implicit dereference
    add(2, 3);

    // Step 2.1.b
    GreetPtr greet = &Greet;
    std::cout << greet("Ole") << std::endl;

    // Step 2.1.c
    int intArray1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    FilterAndPrint(intArray1, 10, &IsEven);
    FilterAndPrint(intArray1, 10, &IsOdd);

    // Step 2.1.d
    void(*fPtrList[])() = {&Play, &Pause, &Quit};
    for (unsigned int i = 0; i < 3; i++)
        fPtrList[i]();
    

    // Step 3.1.c

    // Process integers
    std::cout << "intArray before: ";
    for (unsigned int i = 0; i < 10; i++) {
        std::cout << intArray1[i] << ' ';
    } std::cout << std::endl;

    ProcessArray(intArray1, 10, &DoubleInt);

    std::cout << "intArray after: ";
    for (unsigned int i = 0; i < 10; i++) {
        std::cout << intArray1[i] << ' ';
    } std::cout << std::endl;

    // Process characters
    char charArray[10] = { 'a', 'z', 'c', 'f', 'j', 'i', 'l', 'p', 'q', 't'};
    std::cout << "charArray before: ";
    for (unsigned int i = 0; i < 10; i++) {
        std::cout << charArray[i] << ' ';
    } std::cout << std::endl;

    ProcessArray(charArray, 10, &CapitalizeChar);

    std::cout << "charArray after: ";
    for (unsigned int i = 0; i < 10; i++) {
        std::cout << charArray[i] << ' ';
    } std::cout << std::endl;

    TDataAggregator<float> agg {};
    float val = 4.5;
    agg.Accumulate(val);
    TDataAggregator<float>::StaticCallback(val, &agg);
    int intArray2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    const int size = _countof(intArray2);
    const int arraySum = (size / 2) * (intArray2[0] + intArray2[size - 1]);

    TDataAggregator<int> intAgg {};
    ProcessWithContext<int>(intArray2, 10, TDataAggregator<int>::StaticCallback, &intAgg);
    std::cout << "Share total: " << intAgg.Get() << ", Array sum = " << arraySum << std::endl;

    return 0;
}