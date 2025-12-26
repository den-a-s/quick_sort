# Quick Sort

##  Зависимости

### Ubuntu/Debian
(так же для WSL)
```bash
# Основные инструменты
sudo apt update
sudo apt install -y build-essential cmake g++ git gdb

# Google Test
sudo apt install -y libgtest-dev

# Valgrind (для проверки памяти - опционально)
sudo apt install -y valgrind
```

## 🔨 Сборка проекта

### Вариант 1: Базовая сборка
```bash
# 1. Клонируйте проект или создайте структуру
git clone <ссылка на репозиторий>
cd dynamic_array

# 2. Создайте директорию сборки
mkdir build
cd build

# 3. Настройте CMake
cmake ..

# 4. Запустите тесты
./array_tests
```

### Вариант 2: Отладочная сборка с Valgrind
```bash
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make -j$(nproc)

# Проверка памяти
valgrind --leak-check=full ./array_tests

# Или используйте цели CMake
make valgrind
```

### Вариант 3: Разработка в VS Code
#### Расширения
Установите данные расширения

- WSL (если под Windows)

- C/C++ Extension Pack  (ms-vscode.cpptools)

- CMake Tools (ms-vscode.cmake-tools)

Потом можно пользоваться прямо из редактора, он подтянет и код и CMakeLists и дебаг в редакторе
