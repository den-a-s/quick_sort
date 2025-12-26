cmake_minimum_required(VERSION 3.10)
project(QuickSort VERSION 1.0.0 LANGUAGES CXX)

# Настройка стандарта C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Опции сборки
option(BUILD_TESTS "Build tests" ON)
option(BUILD_EXAMPLES "Build examples" ON)

set(DATA_FILE_PATH ${CMAKE_SOURCE_DIR}/experiment.csv)

# Включаем проверки в отладочном режиме
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-D_DEBUG)
endif()

add_executable(QuickSortMain main.cpp)
target_link_directories(QuickSortMain PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_compile_definitions(QuickSortMain PRIVATE 
    DATA_FILE_PATH="${DATA_FILE_PATH}"
)

# Тесты
if(BUILD_TESTS)
    # Поиск Google Test
    find_package(GTest REQUIRED)
    find_package(Threads REQUIRED)
    
    # Создаем тестовый исполняемый файл
    add_executable(quick_sort_tests tests/quick_sort_tests.cpp)
    
    # Подключаем зависимости
    target_link_libraries(quick_sort_tests 
        GTest::gtest
        GTest::gtest_main
        Threads::Threads
    )
    
    # Добавляем путь к заголовкам для тестов
    target_include_directories(quick_sort_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
    
    # Добавляем тесты в CTest
    include(GoogleTest)
    gtest_discover_tests(quick_sort_tests)
    
    message(STATUS "Building tests")
endif()
