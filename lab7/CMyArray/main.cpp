#include "MyArray/MyArray.hpp"
#include <string>
#include <iostream>

template<class T>
void PrintArray(const MyArray<T> & array)
{
    // std::cout << "Direct order" << std::endl;
    // for (auto it = array.begin(); it != array.end(); it++)
    // {
    //     std::cout << *it << std::endl;
    // }

    // std::cout << "Reverse order" << std::endl;
    // for (auto it = array.rbegin(); it != array.rend(); it++)
    // {
    //     std::cout << *it << std::endl;
    // }
}

int main(int argc, char const *argv[])
{
    MyArray<double> array;

    array.Push(4.4);
    array.Push(4.3);

    return 0;
}


int main1(int argc, char const *argv[])
{
    {
        MyArray<double> array;

        array.Push(4.4);
        array.Push(1.4);
        array.Push(9.4);
        array.Push(6.4);

        PrintArray(array);
    }
    {
        MyArray<std::string> array;

        array.Push("vector");
        array.Push("string");
        array.Push("map");

        PrintArray(array);
    }

    return 0;
}
