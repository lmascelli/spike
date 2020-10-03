#include "spike_lib.hpp"
#include "spike_math.hpp"
#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
    SPIKE::Raw_Data data = SPIKE::load_data("data");
    for (auto a : data.data)
    {
        cout << a << " ";
    }
    cout << endl;
    cout << "mean: " << data.mean() << " , std: " << data.std() << endl;
    return 0;
}