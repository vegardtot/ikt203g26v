#include <iostream>

#include "template.h"

/// Disable automatic padding for the purpose to see
/// that the sizeof TMyStruct is the sum of the fields
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

int main() {

    constexpr int a = 3;
    constexpr double b = 3.1;

    PrintTypeSize(a);
    PrintTypeSize(b);
    PrintTypeSize(TMyStruct{
        .foo = b,
        .bar = a,
    });

    std::cout << "Max(1, 5) = " << GetMax(1, 5) << std::endl;

    constexpr TStudent s1 = {.grade = 3};
    constexpr TStudent s2 = {.grade = 5};

    std::cout << "Max(s1, s2) = " << GetMax(s1, s2).grade << std::endl;

    return 0;
}