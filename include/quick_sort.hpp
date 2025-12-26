#include <cstdlib>
#include <cstring>
#include <cassert>
#include <utility>
#include <memory>

#include <iostream>

template <typename RandomIt, typename Compare>
typename std::iterator_traits<RandomIt>::value_type
median_of_three(RandomIt left, RandomIt right, Compare comp)
{
    RandomIt i = left;
    RandomIt mid = left + (right - left) / 2;
    RandomIt j = right - 1;

    if (comp(*mid, *i))
        std::iter_swap(i, mid);
    if (comp(*j, *mid))
        std::iter_swap(mid, j);
    if (comp(*mid, *i))
        std::iter_swap(i, mid);

    return *mid;
}

template <typename RandomIt, typename Compare>
void insertion_sort(RandomIt left, RandomIt right, Compare comp)
{
    using value_type = typename std::iterator_traits<RandomIt>::value_type;

    for (RandomIt i = left + 1; i < right; ++i)
    {
        value_type key = std::move(*i);
        RandomIt j = i;
        while (j > left && comp(key, *(j - 1)))
        {
            *j = std::move(*(j - 1));
            --j;
        }
        *j = std::move(key);
    }
}

template <typename RandomIt, typename Compare, int Threshold = 16>
void quicksort_threshold(RandomIt left, RandomIt right, Compare comp)
{
    static_assert(
        std::is_same<
            typename std::iterator_traits<RandomIt>::iterator_category,
            std::random_access_iterator_tag>::value,
        "quick_sort requires random access iterators");

    using value_type = typename std::iterator_traits<RandomIt>::value_type;

    if (left >= right)
        return;

    while (right - left > Threshold)
    {
        value_type pivot = median_of_three(left, right, comp);

        RandomIt i = left;
        RandomIt j = right - 1;
        while (true)
        {
            while (comp(*i, pivot))
            {
                ++i;
            }
            while (comp(pivot, *j))
            {
                --j;
            }
            if (i >= j)
            {
                break;
            }
            std::iter_swap(i, j);
            ++i;
            --j;
        }

        RandomIt mid = j + 1;

        if (mid - left < right - mid)
        {
            quicksort_threshold(left, mid, comp);
            left = mid;
        }
        else
        {
            quicksort_threshold(mid, right, comp);
            right = mid;
        }
    }

    if (right - left > 1)
    {
        insertion_sort(left, right, comp);
    }
}

template <typename RandomIt, typename Compare>
void quicksort(RandomIt left, RandomIt right, Compare comp)
{
    // Проверяем, что итераторы действительно random access
    static_assert(
        std::is_same<
            typename std::iterator_traits<RandomIt>::iterator_category,
            std::random_access_iterator_tag>::value,
        "quick_sort requires random access iterators");

    using value_type = typename std::iterator_traits<RandomIt>::value_type;

    if (left >= right)
        return;

    value_type pivot = median_of_three(left, right, comp);

    RandomIt i = left;
    RandomIt j = right - 1;
    while (true)
    {
        while (comp(*i, pivot))
        {
            ++i;
        }
        while (comp(pivot, *j))
        {
            --j;
        }
        if (i >= j)
        {
            break;
        }
        std::iter_swap(i, j);
        ++i;
        --j;
    }

    RandomIt mid = j + 1;

    if (mid - left < right - mid)
    {
        quicksort(left, mid, comp);
        left = mid;
    }
    else
    {
        quicksort(mid, right, comp);
        right = mid;
    }
}
