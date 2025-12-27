#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
#include <random>
#include "quick_sort.hpp"

// Вспомогательные функции
template <typename T>
std::vector<T> generate_sorted_vector(size_t size)
{
    std::vector<T> vec(size);
    for (size_t i = 0; i < size; ++i)
    {
        vec[i] = static_cast<T>(i);
    }
    return vec;
}

template <typename T>
std::vector<T> generate_reverse_sorted_vector(size_t size)
{
    std::vector<T> vec(size);
    for (size_t i = 0; i < size; ++i)
    {
        vec[i] = static_cast<T>(size - i - 1);
    }
    return vec;
}

template <typename T>
std::vector<T> generate_random_vector(size_t size)
{
    std::vector<T> vec(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<T> dist(-1000, 1000);

    for (size_t i = 0; i < size; ++i)
    {
        vec[i] = dist(gen);
    }
    return vec;
}

// Тесты для insertion_sort
TEST(InsertionSortTest, SingleElement)
{
    std::vector<int> vec = {42};
    std::vector<int> expected = {42};

    insertion_sort(vec.begin(), vec.end(), std::less<int>());
    EXPECT_EQ(vec, expected);
}

TEST(InsertionSortTest, TwoElementsUnsorted)
{
    std::vector<int> vec = {5, 2};
    std::vector<int> expected = {2, 5};

    insertion_sort(vec.begin(), vec.end(), std::less<int>());
    EXPECT_EQ(vec, expected);
}

TEST(InsertionSortTest, TwoElementsSorted)
{
    std::vector<int> vec = {2, 5};
    std::vector<int> expected = {2, 5};

    insertion_sort(vec.begin(), vec.end(), std::less<int>());
    EXPECT_EQ(vec, expected);
}

TEST(InsertionSortTest, TenElementsSorted)
{
    std::vector<int> vec = generate_sorted_vector<int>(10);
    std::vector<int> expected = vec;

    insertion_sort(vec.begin(), vec.end(), std::less<int>());
    EXPECT_EQ(vec, expected);
}

TEST(InsertionSortTest, TenElementsReverseSorted)
{
    std::vector<int> vec = generate_reverse_sorted_vector<int>(10);
    std::vector<int> expected = generate_sorted_vector<int>(10);

    insertion_sort(vec.begin(), vec.end(), std::less<int>());
    EXPECT_EQ(vec, expected);
}

TEST(QuickSortTest, SingleElement)
{
    std::vector<int> vec = {42};
    std::vector<int> expected = {42};

    quicksort(vec.begin(), vec.end(), std::less<int>());
    EXPECT_EQ(vec, expected);
}

TEST(QuickSortTest, TwoElementsUnsorted)
{
    std::vector<int> vec = {5, 2};
    std::vector<int> expected = {2, 5};

    quicksort(vec.begin(), vec.end(), std::less<int>());
    EXPECT_EQ(vec, expected);
}

TEST(QuickSortTest, TwoElementsSorted)
{
    std::vector<int> vec = {2, 5};
    std::vector<int> expected = {2, 5};

    quicksort(vec.begin(), vec.end(), std::less<int>());
    EXPECT_EQ(vec, expected);
}

TEST(QuickSortTest, TenElementsSorted)
{
    std::vector<int> vec = generate_sorted_vector<int>(10);
    std::vector<int> expected = vec;

    quicksort(vec.begin(), vec.end(), std::less<int>());
    EXPECT_EQ(vec, expected);
}

TEST(QuickSortTest, TenElementsReverseSorted)
{
    std::vector<int> vec = generate_reverse_sorted_vector<int>(10);
    std::vector<int> expected = generate_sorted_vector<int>(10);

    quicksort(vec.begin(), vec.end(), std::less<int>());
    EXPECT_EQ(vec, expected);
}

TEST(QuickSortTest, RandomElements)
{
    std::vector<int> vec = generate_random_vector<int>(100);
    std::vector<int> expected = vec;

    quicksort(vec.begin(), vec.end(), std::less<int>());
    std::sort(expected.begin(), expected.end(), std::less<int>());

    EXPECT_EQ(vec, expected);
}

TEST(QuickSortThresholdTest, SingleElement)
{
    std::vector<int> vec = {42};
    std::vector<int> expected = {42};

    itmo_sort(vec.begin(), vec.end(), std::less<int>());
    EXPECT_EQ(vec, expected);
}

TEST(QuickSortThresholdTest, TwoElementsSorted)
{
    std::vector<int> vec = {2, 5};
    std::vector<int> expected = {2, 5};

    itmo_sort(vec.begin(), vec.end(), std::less<int>());
    EXPECT_EQ(vec, expected);
}

TEST(QuickSortThresholdTest, TwoElementsUnsorted)
{
    std::vector<int> vec = {5, 2};
    std::vector<int> expected = {2, 5};

    itmo_sort(vec.begin(), vec.end(), std::less<int>());
    EXPECT_EQ(vec, expected);
}

TEST(QuickSortThresholdTest, TenElementsSorted)
{
    std::vector<int> vec = generate_sorted_vector<int>(10);
    std::vector<int> expected = vec;

    itmo_sort(vec.begin(), vec.end(), std::less<int>());
    EXPECT_EQ(vec, expected);
}

TEST(QuickSortThresholdTest, TenElementsReverseSorted)
{
    std::vector<int> vec = generate_reverse_sorted_vector<int>(10);
    std::vector<int> expected = generate_sorted_vector<int>(10);

    itmo_sort(vec.begin(), vec.end(), std::less<int>());
    EXPECT_EQ(vec, expected);
}

TEST(QuickSortThresholdTest, ExactlyThresholdSize)
{
    // Проверяем на размере равном порогу (16)
    std::vector<int> vec = generate_random_vector<int>(16);
    std::vector<int> expected = vec;

    itmo_sort(vec.begin(), vec.end(), std::less<int>());
    std::sort(expected.begin(), expected.end());

    EXPECT_EQ(vec, expected);
}

TEST(QuickSortThresholdTest, LessThanThresholdSize)
{
    // Проверяем на размере меньше порога (15)
    std::vector<int> vec = generate_random_vector<int>(15);
    std::vector<int> expected = vec;

    itmo_sort(vec.begin(), vec.end(), std::less<int>());
    std::sort(expected.begin(), expected.end());

    EXPECT_EQ(vec, expected);
}

TEST(QuickSortThresholdTest, GreaterThanThresholdSize)
{
    // Проверяем на размере больше порога (17)
    std::vector<int> vec = generate_random_vector<int>(17);
    std::vector<int> expected = vec;

    itmo_sort(vec.begin(), vec.end(), std::less<int>());
    std::sort(expected.begin(), expected.end(), std::less<int>());

    EXPECT_EQ(vec, expected);
}

TEST(QuickSortThresholdTest, RandomElements)
{
    std::vector<int> vec = generate_random_vector<int>(100);
    std::vector<int> expected = vec;

    itmo_sort(vec.begin(), vec.end(), std::less<int>());
    std::sort(expected.begin(), expected.end(), std::less<int>());

    EXPECT_EQ(vec, expected);
}

TEST(QuickSortTest, CustomComparator)
{
    std::vector<int> vec = {5, 2, 8, 1, 9};
    std::vector<int> expected_asc = {1, 2, 5, 8, 9};
    std::vector<int> expected_desc = {9, 8, 5, 2, 1};

    // По возрастанию
    quicksort(vec.begin(), vec.end(), std::less<int>());
    EXPECT_EQ(vec, expected_asc);

    // По убыванию
    vec = {5, 2, 8, 1, 9};
    quicksort(vec.begin(), vec.end(), std::greater<int>());
    EXPECT_EQ(vec, expected_desc);
}

TEST(QuickSortTest, DoubleType)
{
    std::vector<double> vec = {3.14, 2.71, 1.41, 0.0, -1.0};
    std::vector<double> expected = {-1.0, 0.0, 1.41, 2.71, 3.14};

    quicksort(vec.begin(), vec.end(), std::less<double>());

    for (size_t i = 0; i < vec.size(); ++i)
    {
        EXPECT_DOUBLE_EQ(vec[i], expected[i]);
    }
}

TEST(QuickSortTest, EmptyRange)
{
    std::vector<int> vec;

    // Не должно вызывать ошибок
    quicksort(vec.begin(), vec.end(), std::less<int>());
    itmo_sort(vec.begin(), vec.end(), std::less<int>());
    insertion_sort(vec.begin(), vec.end(), std::less<int>());

    EXPECT_TRUE(vec.empty());
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}