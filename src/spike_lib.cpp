#include "spike_lib.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
using std::cout, std::endl;

SPIKE::Raw_Data &SPIKE::load_data(std::string file)
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
        return *data;
    }
    else
    {
        cout << "Error loading file" << endl;
        exit(-1);
    }
}

double SPIKE::Raw_Data::mean()
{
    if (computed_mean)
        return t_mean;
    else
    {

        double sum = 0;
        for (auto d : data)
        {
            sum += d;
        }
        t_mean = sum / data.size();
        computed_mean = true;
        return t_mean;
    }
}

double SPIKE::Raw_Data::std()
{
    if (computed_std)
        return t_std;
    else
    {
        double t_mean = mean();
        double sum = 0;
        for (auto d : data)
        {
            sum += pow(d - t_mean, 2);
        }
        t_std = sum / data.size();
        computed_std = true;
        return t_std;
    }
}

SPIKE::Raw_Data::~Raw_Data()
{
    cout << "Raw_Data destroyed." << endl;
}

SPIKE::Spike_Train &SPIKE::hard_thresold(SPIKE::Raw_Data &data)
{
    Spike_Train *t = new Spike_Train;

    return *t;
}