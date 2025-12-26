#!/usr/bin/env python3
"""
Скрипт для построения графиков сравнения алгоритмов сортировки.
Использование: python script.py <csv_file> [--max N] [--min N] [--step N]
"""

import sys
import os

def parse_arguments():
    """Парсинг аргументов командной строки"""
    args = sys.argv[1:]
    
    if not args:
        print("Использование: python script.py <csv_file> [--max N] [--min N] [--step N]")
        print("Примеры:")
        print("  python script.py experiment.csv")
        print("  python script.py experiment.csv --max 50")
        print("  python script.py experiment.csv --min 10 --max 100")
        print("  python script.py experiment.csv --max 200 --step 10")
        sys.exit(1)
    
    csv_file = args[0]
    
    max_elements = None
    min_elements = None
    step = 5  
    
    i = 1
    while i < len(args):
        if args[i] == '--max' and i + 1 < len(args):
            max_elements = int(args[i + 1])
            i += 2
        elif args[i] == '--min' and i + 1 < len(args):
            min_elements = int(args[i + 1])
            i += 2
        elif args[i] == '--step' and i + 1 < len(args):
            step = int(args[i + 1])
            i += 2
        else:
            print(f"Неизвестный аргумент: {args[i]}")
            i += 1
    
    return csv_file, max_elements, min_elements, step

def main():
    csv_file, max_elements, min_elements, step = parse_arguments()
    
    if not os.path.exists(csv_file):
        print(f"Ошибка: Файл '{csv_file}' не найден")
        sys.exit(1)
    
    data = pd.read_csv(csv_file)
    
    original_count = len(data)
    
    if min_elements is not None:
        data = data[data['Size'] >= min_elements]
    
    if max_elements is not None:
        data = data[data['Size'] <= max_elements]
    
    filtered_count = len(data)
    print(f"Загружено записей: {original_count}")
    print(f"Отфильтровано записей: {filtered_count}")
    
    if filtered_count == 0:
        print("Ошибка: Нет данных после фильтрации")
        sys.exit(1)
    
    plt.figure(figsize=(12, 8))
    
    algorithms = data['Algorithm'].unique()
    
    for algo in algorithms:
        algo_data = data[data['Algorithm'] == algo]
        algo_data = algo_data.sort_values('Size')  
        plt.plot(algo_data['Size'], algo_data['Time (µs)'], 
                 marker='o', markersize=4, linewidth=2, label=algo)
    
    x_min = data['Size'].min()
    x_max = data['Size'].max()
    
    if step <= 0:
        step = 5
    
    plt.xticks(range(x_min, x_max + 1, step))
    
    plt.xlabel('Size (количество элементов)', fontsize=12)
    plt.ylabel('Time (µs)', fontsize=12)
    
    title = 'Сравнение времени выполнения алгоритмов сортировки'
    if min_elements is not None or max_elements is not None:
        title += f' ('
        if min_elements is not None:
            title += f'min={min_elements}'
            if max_elements is not None:
                title += ', '
        if max_elements is not None:
            title += f'max={max_elements}'
        title += ')'
    
    plt.title(title, fontsize=14, fontweight='bold')
    plt.legend(fontsize=10)
    plt.grid(True, alpha=0.3)
    plt.tight_layout()
    
    base_name = os.path.splitext(csv_file)[0]
    
    if min_elements is not None and max_elements is not None:
        output_file = f"{base_name}_{min_elements}_to_{max_elements}.png"
    elif max_elements is not None:
        output_file = f"{base_name}_to_{max_elements}.png"
    elif min_elements is not None:
        output_file = f"{base_name}_from_{min_elements}.png"
    else:
        output_file = f"{base_name}_all.png"
    
    plt.savefig(output_file, dpi=300, bbox_inches='tight')
    print(f"График сохранен в файл '{output_file}'")
    print(f"Диапазон размеров на графике: {x_min} - {x_max}")


if __name__ == "__main__":
    # Устанавливаем неинтерактивный бэкенд для Matplotlib
    import matplotlib
    matplotlib.use('Agg')
    import matplotlib.pyplot as plt
    import pandas as pd
    
    main()
