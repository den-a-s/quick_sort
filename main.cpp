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

#include "include/quick_sort.hpp"
// Генерация тестовых данных
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

// Основная функция эксперимента
template <typename Container, typename Compare>
void run_sorting_experiment(
    Container const &data, // Массив для сортировки (по ссылке)
    Compare comp,
    std::ofstream &outfile // Файл для записи результатов
)
{
    using T = typename Container::value_type;

    size_t size = data.size();

    // Делаем копию данных для сортировки
    Container data_copy = data;

    // Замеряем время сортировки
    auto start = std::chrono::high_resolution_clock::now();
    quicksort(data_copy.begin(), data_copy.end(), comp);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    long long time_us = duration.count();

    // Проверяем корректность сортировки
    bool sorted_correctly = std::is_sorted(data_copy.begin(), data_copy.end());

    // Записываем результаты в файл
    outfile << "Size: " << size
            << " | Time: " << time_us << " µs"
            << " | Sorted: " << (sorted_correctly ? "YES" : "NO")
            << std::endl;
}

// Основная функция эксперимента
template <typename Container, typename Compare>
void run_sorting_experiment_with_treshold(
    Container const &data, // Массив для сортировки (по ссылке)
    Compare comp,
    int treshold,
    std::ofstream &outfile // Файл для записи результатов
)
{
    using T = typename Container::value_type;

    size_t size = data.size();

    // Делаем копию данных для сортировки
    Container data_copy = data;

    // Замеряем время сортировки
    auto start = std::chrono::high_resolution_clock::now();
    optimized_quicksort(data_copy.begin(), data_copy.end(), comp, treshold);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    long long time_us = duration.count();

    // Проверяем корректность сортировки
    bool sorted_correctly = std::is_sorted(data_copy.begin(), data_copy.end());

    // Записываем результаты в файл
    outfile << "Size: " << size
            << " | Time: " << time_us << " µs"
            << " | Sorted: " << (sorted_correctly ? "YES" : "NO")
            << " | Treshold " << treshold
            << std::endl;
}

int main()
{
    std::string filename = "experiment.txt";
    std::ofstream file(filename, std::ios::out);
    if (!file)
    {
        std::cerr << "Can't open file: " << filename << std::endl;
        return 0;
    }

    auto data = generate_data(1000000, DataType::REVERSED);
    run_sorting_experiment(data, std::less<int>(), file);
    for (int curr_treshold = 4; curr_treshold < 30; curr_treshold++)
    {
        run_sorting_experiment_with_treshold(data, std::less<int>(), curr_treshold, file);
    }

    file.close();
    return 0;
}