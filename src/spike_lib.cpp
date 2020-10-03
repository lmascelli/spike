#include "spike_lib.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
using std::cout, std::endl;

// Parsing a text file into a Raw_Data structure.
// The file must be done this way:
// SAMPLING FREQUENCY\n
// RAW DATAS separated by a space.
//

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

// Return the mean if already computed or compute it and return if not.

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
// Return the standard deviation if already computed or compute it and return if not.

double SPIKE::Raw_Data::std()
{
    if (computed_std)
        return t_std;
    else
    {
        double m_mean = mean();
        double sum = 0;
        for (auto d : data)
        {
            sum += pow(d - m_mean, 2);
        }
        t_std = sqrt(sum / data.size());
        computed_std = true;
        return t_std;
    }
}

SPIKE::Raw_Data::~Raw_Data()
{
    cout << "Raw_Data destroyed." << endl;
}

// Compute the hard threshold of the data at 3 standard deviation.
// Return a Spike_Train structure.
SPIKE::Spike_Train &SPIKE::hard_thresold(SPIKE::Raw_Data &data)
{
    Spike_Train *t = new Spike_Train;
    const double raw_data_bin_size = 1 / data.sampling_frequency;
    const size_t window_size = ceil(SPIKE_DURATION * data.sampling_frequency);
    size_t end = data.data.size() - window_size;
    for (size_t i = 0; i < end; i += window_size)
    {
        double min, max;
        min = max = data.data[i];
        for (int j = 1; j < window_size; j++)
        {
            if (data.data[i + j] > max)
                max = data.data[i + j];
            if (data.data[i + j] < min)
                min = data.data[i + j];
        }
        if (max - min > 1 * data.std())
            t->data.push_back(1);
        else
            t->data.push_back(0);
    }
    return *t;
}

/* Compute the Inter Spike Interval of an element of a Group.



*/
// It seems to count the initial span to the first spike also if the train does
// not start with a spike.
std::vector<unsigned int> SPIKE::Group::isi(int n)
{
    std::vector<unsigned int> &train = this->el[n].data;
    std::vector<unsigned int> res;
    res.resize(ISI_MAX, 0);
    int i = 0;
    while (train[i] != 0)
        i++;
    int j = 0;
    while (i < train.size())
    {
        if (train[++i] == 1)
        {
            res[j]++;
            j = 0;
        }
        else
            j++;
    }
    return res;
}