#include "spike_lib.hpp"
#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
    SPIKE::Raw_Data data = SPIKE::load_data("data");
    SPIKE::Group group;
    cout << "mean: " << data.mean() << ", std: " << data.std() << endl;
    group.el.push_back(SPIKE::hard_thresold(data));
    auto isi = group.isi(0);
    for (auto i : group.el[0].data)
        cout << i << ", ";
    cout << endl;
    for (auto i : group.isi(0))
        cout << i << ", ";
    cout << endl;
    return 0;
}