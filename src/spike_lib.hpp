#pragma once
#include <vector>
#include <string>

namespace SPIKE
{
    struct Raw_Data
    {
        double sampling_frequency = 0;
        std::vector<double> data;
        double mean = 0;
        double std = 0;
    };

    Raw_Data *load_data(std::string file);
} // namespace SPIKE