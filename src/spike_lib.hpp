#pragma once
#include <vector>
#include <string>

#define SPIKE_DURATION 0.003
#define ISI_MAX 100

namespace SPIKE
{
    class Spike_Train
    {
    public:
        std::vector<unsigned int> data;
        double bin_size = 0;
    };

    class Raw_Data
    {
    public:
        double sampling_frequency = 0;
        std::vector<double> data;

        double mean();
        double std();
        ~Raw_Data();

    private:
        double t_mean = 0;
        double t_std = 0;
        bool computed_mean = false, computed_std = false;
    };

    class Group
    {
    public:
        std::vector<Spike_Train> el;
        std::vector<unsigned int> isi(int i);
    };

    Raw_Data &load_data(std::string file);
    Spike_Train &hard_thresold(Raw_Data &d);
} // namespace SPIKE