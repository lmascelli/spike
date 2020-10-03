#include "spike_lib.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
using std::cout, std::endl;

SPIKE::Raw_Data *SPIKE::load_data(std::string file)
{
    std::ifstream raw_data_file(file);
    if (raw_data_file.is_open())
    {
        Raw_Data *data = new Raw_Data;
        std::string temp;
        std::getline(raw_data_file, temp);
        data->sampling_frequency = std::stod(temp);
        while (std::getline(raw_data_file, temp, ' '))
        {
            data->data.push_back(std::stod(temp));
        }
        return data;
    }
    else
    {
        cout << "Error loading file" << endl;
        exit(-1);
    }
}