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
    RandomIt mid = left + (right - 1 - left) / 2;
    RandomIt right_tmp = right - 1;

    if (comp(*mid, *left))
        std::iter_swap(left, mid);
    if (comp(*right_tmp, *left))
        std::iter_swap(left, right_tmp);
    if (comp(*right_tmp, *mid))
        std::iter_swap(right_tmp, mid);

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

template <typename RandomIt, typename Compare>
RandomIt partition(RandomIt left, RandomIt right, Compare comp)
{
    using value_type = typename std::iterator_traits<RandomIt>::value_type;
}

template <typename RandomIt, typename Compare, int Threshold = 16>
void itmo_sort(RandomIt left, RandomIt right, Compare comp)
{
    static_assert(
        std::is_same<
            typename std::iterator_traits<RandomIt>::iterator_category,
            std::random_access_iterator_tag>::value,
        "quick_sort requires random access iterators");

    using value_type = typename std::iterator_traits<RandomIt>::value_type;

    if (right - left <= 1)
        return;

    // так как right указатель на конец.
    while (right - 1 - left > Threshold - 1)
    {
        value_type pivot = median_of_three(left, right, comp);

        RandomIt i = left - 1;
        RandomIt j = right;
        while (true)
        {
            do
            {
                ++i;
            } while (comp(*i, pivot));

            do
            {
                --j;
            } while (comp(pivot, *j));

            if (i >= j)
            {
                break;
            }
            std::iter_swap(i, j);
        }

        RandomIt mid = j;

        if (mid - left < right - mid)
        {
            itmo_sort<RandomIt, Compare, Threshold>(left, mid + 1, comp);
            left = mid + 1;
        }
        else
        {
            itmo_sort<RandomIt, Compare, Threshold>(mid + 1, right, comp);
            right = mid + 1;
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
    itmo_sort<RandomIt, Compare, 1>(left, right, comp);
}
