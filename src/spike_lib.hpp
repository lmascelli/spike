#pragma once
#include <vector>
#include <string>

#define SPIKE_DURATION 0.003
#define ISI_MAX 100

namespace SPIKE
{

    // The Spike_Train class is the abstraction for Spike_Train data.
    class Spike_Train
    {
    public:
        std::vector<unsigned int> data;
        double bin_size = 0;
    };

    // The Raw_Data class is an abstraction for reading different data format.
    // It holds and compute the simples statistics of raw data as mean and std;
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

    // The Group class is meant to be a collection of spike trains from different electrodes.
    class Group
    {
    public:
        std::vector<Spike_Train> el;
        std::vector<unsigned int> isi(int i);
        // TODO Maybe create a matrix struct for returning 2D array.
        std::vector<unsigned int> cisi(int i, int j);
    };

    Raw_Data &load_data(std::string file);
    Spike_Train &hard_thresold(Raw_Data &d);
} // namespace SPIKE