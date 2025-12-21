#include <cstdlib>
#include <cstring>
#include <cassert>
#include <utility>
#include <memory>

#include <iostream>

template <typename RandomIt, typename Compare>
static RandomIt get_pivot(RandomIt left, RandomIt right, Compare comp)
{
    using value_type = typename std::iterator_traits<RandomIt>::value_type;
    // Вычисляем середину
    RandomIt middle = left + (right - left) / 2;

    // Медиана из трех: left, middle, right-1
    if (comp(*middle, *left))
    {
        std::iter_swap(left, middle);
    }
    if (comp(*(right - 1), *left))
    {
        std::iter_swap(left, right - 1);
    }
    if (comp(*(right - 1), *middle))
    {
        std::iter_swap(middle, right - 1);
    }

    return middle;
}

template <typename RandomIt, typename Compare>
static void insertion_sort(RandomIt left, RandomIt right, Compare comp)
{
    using value_type = typename std::iterator_traits<RandomIt>::value_type;
    for (RandomIt i = left + 1; i < right; ++i)
    {
        value_type key = std::move(*i);
        RandomIt j = i - 1;

        while (j >= left && comp(key, *j))
        {
            std::iter_swap(j, j + 1);
            --j;
        }
        *(j + 1) = std::move(key);
    }
}

template <typename RandomIt, typename Compare>
void optimized_quicksort(RandomIt left, RandomIt right, Compare comp, size_t threshold)
{
    static_assert(
        std::is_same<
            typename std::iterator_traits<RandomIt>::iterator_category,
            std::random_access_iterator_tag>::value,
        "optimized_quicksort requires random access iterators");

    // Базовый случай - 0 или 1 элемент
    if (left >= right || std::next(left) == right)
        return;

    using difference_type = typename std::iterator_traits<RandomIt>::difference_type;
    using value_type = typename std::iterator_traits<RandomIt>::value_type;

    while (right - left > static_cast<difference_type>(threshold))
    {
        // Опорный элемент - медиана
        RandomIt middle = get_pivot(left, right, comp);
        value_type pivot = *middle;
        std::iter_swap(middle, right - 2);

        // Разбиение Ломуто
        RandomIt i = left;
        for (RandomIt j = left; j < right - 2; ++j)
        {
            if (comp(*j, pivot))
            {
                std::iter_swap(i, j);
                ++i;
            }
        }
        std::iter_swap(i, right - 2);

        // Исключение хвостовой рекурсии: сортируем меньший интервал рекурсивно
        difference_type left_size = i - left;
        difference_type right_size = (right - i) - 1;

        if (left_size < right_size)
        {
            optimized_quicksort(left, i, comp, threshold);
            left = i + 1;
        }
        else
        {
            optimized_quicksort(i + 1, right, comp, threshold);
            right = i;
        }
    }

    // Сортировка вставками для коротких интервалов
    insertion_sort(left, right, comp);
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

    using difference_type = typename std::iterator_traits<RandomIt>::difference_type;

    // Базовый случай - 0 или 1 элемент
    if (left >= right || std::next(left) == right)
        return;

    RandomIt i = left;
    RandomIt j = std::prev(right); // Указатель на последний элемент
    RandomIt pivot_it = left + (std::distance(left, right) / 2);
    auto pivot = *pivot_it;

    // Разделение массива (Хоара)
    while (i <= j)
    {
        // Ищем элемент слева, который должен быть справа от pivot
        while (comp(*i, pivot))
        {
            ++i;
        }

        // Ищем элемент справа, который должен быть слева от pivot
        while (comp(pivot, *j))
        {
            --j;
        }

        // Меняем местами, если индексы не пересеклись
        if (i <= j)
        {
            std::iter_swap(i, j);
            ++i;
            if (j != left)
                --j; // Избегаем выхода за границы
        }
    }

    // Рекурсивно сортируем левую и правую части
    if (left < j)
    {
        quicksort(left, std::next(j), comp); // std::next(j) т.к. правая граница - exclusive
    }
    if (i < right)
    {
        quicksort(i, right, comp);
    }
}
