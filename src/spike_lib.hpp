#pragma once
#include <vector>
#include <string>

namespace SPIKE
{

    class Spike_Train
    {
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

    Raw_Data &load_data(std::string file);
    Spike_Train &hard_thresold(Raw_Data &d);
} // namespace SPIKE