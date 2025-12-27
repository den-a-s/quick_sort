#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>
#include <iomanip>
#include <climits>
#include <iterator>
#include <concepts>
#include <fstream>
#include <functional>

#include "include/quick_sort.hpp"

enum class DataType
{
    RANDOM,
    REVERSED,
};

std::vector<int> generate_data(size_t size, DataType type, int seed = 42)
{
    std::vector<int> data(size);
    std::mt19937 rng(seed);
    std::uniform_int_distribution<int> dist(1, 1000000);

    switch (type)
    {
    case DataType::RANDOM:
        for (size_t i = 0; i < size; ++i)
        {
            data[i] = dist(rng);
        }
        break;

    case DataType::REVERSED:
        for (size_t i = 0; i < size; ++i)
        {
            data[i] = size - i;
        }
        break;
    }

    return data;
}

template <typename Container, typename Compare, typename Sort>
void mesure_sorting(
    Container data,
    Compare comp,
    Sort sort,
    std::string const &name,
    std::ofstream &outfile)
{
    size_t size = data.size();

    auto start = std::chrono::high_resolution_clock::now();
    sort(data.begin(), data.end(), comp);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    long long time_us = duration.count();

    bool sorted_correctly = std::is_sorted(data.begin(), data.end(), comp);

    outfile << name << "," << size << "," << time_us << ","
            << (sorted_correctly ? "YES" : "NO") << std::endl;
}

int main()
{
    std::string filename = DATA_FILE_PATH;
    std::ofstream file(filename, std::ios::out);
    if (!file)
    {
        std::cerr << "Can't open file: " << filename << std::endl;
        return 0;
    }

    file << "Algorithm,Size,Time (µs),Sorted" << std::endl;

    for (int cnt_elem = 4; cnt_elem < 100; cnt_elem++)
    {
        auto data = generate_data(cnt_elem, DataType::REVERSED);
        mesure_sorting(data, std::less<int>(), insertion_sort<std::vector<int>::iterator, std::less<int>>, "insertion_sort", file);
        mesure_sorting(data, std::less<int>(), quicksort<std::vector<int>::iterator, std::less<int>>, "quicksort", file);
        mesure_sorting(data, std::less<int>(), itmo_sort<std::vector<int>::iterator, std::less<int>>, "quicksort_threshold", file);
    }

    file.close();
    return 0;
}