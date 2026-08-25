

#ifndef _TEMPLATE_H
#define _TEMPLATE_H

#include <iostream>
#include <optional>


////////////////////////////////////////////////////////////////////////////////////
/// Step 1.1
////////////////////////////////////////////////////////////////////////////////////

template <typename T> void PrintTypeSize(T v) {
    std::cout << "Size: " << sizeof(T) << std::endl;
}

template <typename T> T GetMax(T a, T b) { return a > b ? a : b; }

////////////////////////////////////////////////////////////////////////////////////
/// Step 1.2
////////////////////////////////////////////////////////////////////////////////////

template <typename... Args>
struct TDataPack;

template <typename Head, typename... Tail>
struct TDataPack<Head, Tail...> {
    Head value;
    TDataPack<Tail...> next;
};

template<> struct TDataPack<> {};

template <typename T, unsigned int size>
class TStaticArray {
  public:
    T items[size]{};

  
    auto Append(const T& item) -> std::optional<unsigned int> {
        if (m_index < size) {
            items[m_index] = item;
            m_index++;
            return m_index - 1;
        }
        return std::nullopt;
    }

    void PrintItems() const {
        for (auto i = 0; i < m_index; i++)
            std::cout << items[i] << ' ';
        std::cout << std::endl;
    }

  private:
    unsigned int m_index{};
};

template <template <typename, int> class Container, typename T, unsigned int N>
auto PrintContainer(const Container<T, N>& container) {
    container.PrintItems();
}

#endif //_TEMPLATE_H