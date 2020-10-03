#pragma once
namespace SPIKE
{
    template <int N>
    inline double unroll_loop(std::vector<double> v, int i)
    {
        return v[i + N - 1] + unroll_loop<N - 1>(v, i);
    }

    template <>
    inline double unroll_loop<0>(std::vector<double> v, int i)
    {
        return 0;
    }

    template <int N>
    double mean(std::vector<double> data)
    {
        double sum = 0;
        for (int i = 0; i < data.size() - N; i += N)
        {
            sum += unroll_loop<N>(data, i);
        }
        for (size_t i = data.size() - N + 1; i < data.size(); i++)
            sum += data[i];
        return sum / data.size();
    }
} // namespace SPIKE
