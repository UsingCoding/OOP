#include "MyArray/MyArray.hpp"
#include <string>
#include <iostream>

template<class T>
void PrintArray(const MyArray<T> & array)
{
    std::cout << "Direct order" << std::endl;
    for (auto it = array.begin(); it != array.end(); it++)
    {
        std::cout << *it << std::endl;
    }

    // for (size_t i = 0; i < array.GetSize(); i++)
    // {
    //     std::cout << array[i] << std::endl;
    // }


    // std::cout << "Size " << array.GetSize() << std::endl;

    std::cout << "Reverse order" << std::endl;
    for (auto it = array.rbegin(); it != array.rend(); it++)
    {
        std::cout << *it << std::endl;
    }
}

int main(int argc, char const *argv[])
{
    MyArray<double> array;

    array.Push(4.4);
    array.Push(5.5);
    array.Push(1.4);

    int i = array.GetSize() - 1;
    for (auto it = array.rbegin(); it != array.rend(); it++, i--)
    {
        // std::cout << (*it == array[i]) << std::endl;
        std::cout << *it << std::endl;
    }

    // MyArray<std::string> array;

    // array.Push("vector");
    // array.Push("string");
    // array.Push("map");
    // // std::cout << array.GetSize() << std::endl;
    // std::cout << array[array.GetSize() - 1] << std::endl;
    // // PrintArray(array);

    return 0;
}
