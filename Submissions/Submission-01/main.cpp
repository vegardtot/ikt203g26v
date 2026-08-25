#include <iostream>
#include <string>

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

    return 0;
}