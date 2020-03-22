#include <iostream>
#include <algorithm>
#include <vector>

void HandleVector(std::vector<int> & vector);
void SortVector(std::vector<int> & vector);

int main(int argc, char const *argv[])
{
    std::vector<int> vector = {1, 2, 3, -4, 12, -7};

    HandleVector(vector);
    SortVector(vector);

    return 0;
}

void HandleVector(std::vector<int> & vector)
{
    int sumOfNeg = 0;
    std::for_each(vector.begin(), vector.end(), [&sumOfNeg](int value) {
        if (value < 0)
        {
            sumOfNeg += value;
        }
    });

    bool odd;
    std::for_each(vector.begin(), vector.end(), [sumOfNeg, &odd](int & value) {
        if (odd)
        {
            value += sumOfNeg;
            odd = false;
        }
        else
        {
            value *= 2;
            odd = true;
        }


    });
}

void SortVector(std::vector<int> & vector)
{
    std::sort(vector.begin(), vector.end());
}
