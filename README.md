# v8_reader

Чтение конфигураций 1С (.cf, .cfu, .cfe, .epf, .erf)

## Описание

Проект предназначен для чтения и разбора файлов конфигураций платформы 1С:Предприятие 8.

![Screenshot](https://github.com/user-attachments/assets/fe0c4235-20eb-4432-b7ff-8a757bd43cde)

Оригинальный проект: https://github.com/fishca/v8_reader

Публикация на Infostart: https://infostart.ru/1c/articles/2610907/

## Структура проекта

```
v8_reader/
├── CMakeLists.txt          # Основной файл сборки CMake
├── README.md               # Документация
├── LICENSE                 # Лицензия
├── .gitignore              # Игнорируемые файлы Git
│
├── src/                    # Исходный код библиотеки
│   ├── *.cpp               # Реализация классов
│   └── *.h                 # Заголовочные файлы
│
├── include/                # Публичные заголовочные файлы
│
├── apps/                   # Приложения
│   ├── gui/                # GUI приложение на wxWidgets
│   │   ├── main.cpp        # Точка входа GUI
│   │   └── mainframe.cpp   # Основное окно
│   └── cli/                # Консольное приложение
│       └── main.cpp        # Точка входа CLI
│
├── tests/                  # Модульные тесты
│
├── docs/                   # Документация
│
├── scripts/                # Скрипты сборки и утилиты
│
└── 3rdparty/               # Сторонние библиотеки
    └── zlib/               # Заголовочные файлы zlib
```

## Требования

### Обязательные
- **CMake** >= 3.16
- **C++ компилятор** с поддержкой C++17 (GCC 7+, Clang 5+, MSVC 2017+)
- **ZLIB** (системная библиотека)

### Опциональные
- **wxWidgets** >= 3.0 (для GUI приложения)
  - Windows: установите с https://www.wxwidgets.org/downloads/
  - Linux: `sudo apt-get install libwxgtk3.0-gtk3-dev` (Ubuntu/Debian)
  - macOS: `brew install wxwidgets`

## Сборка

### Базовая сборка

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

### Опции сборки

| Опция | Описание | По умолчанию |
|-------|----------|--------------|
| `V8_READER_BUILD_GUI` | Собрать GUI приложение | ON |
| `V8_READER_BUILD_CLI` | Собрать консольное приложение | ON |
| `V8_READER_BUILD_TESTS` | Собрать тесты | OFF |

Пример сборки только CLI версии:

```bash
cmake .. -DV8_READER_BUILD_GUI=OFF -DV8_READER_BUILD_CLI=ON
```

### Платформенные особенности

#### Windows (MSVC)

```bash
mkdir build && cd build
cmake .. -G "Visual Studio 17 2022" -A x64
cmake --build . --config Release
```

#### Linux

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . -j$(nproc)
```

#### macOS

```bash
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build . -j$(sysctl -n hw.ncpu)
```

## Установка

```bash
cmake --install . --prefix /usr/local
```

Или для пользовательской установки:

```bash
cmake --install . --prefix ~/.local
```

## Использование

### Консольное приложение

```bash
./v8_reader_cli путь_к_файлу.cf
```

### GUI приложение

Запустите `v8_reader_gui` и откройте файл конфигурации через меню File -> Open.

### Как библиотека

```cpp
#include "APIcfBase.h"

int main() {
    // Инициализация и работа с файлами 1С
    return 0;
}
```

## Поддерживаемые форматы

- `.cf` - файл конфигурации
- `.cfu` - файл обновления конфигурации
- `.cfe` - файл расширения конфигурации
- `.epf` - внешняя обработка
- `.erf` - внешний отчёт

## Разработка

### Добавление новых функций

1. Создайте ветку от `main`
2. Внесите изменения
3. Добавьте тесты (если применимо)
4. Создайте Pull Request

### Запуск тестов

```bash
cmake .. -DV8_READER_BUILD_TESTS=ON
cmake --build .
ctest --test-dir build
```

## Лицензия

Оригинальный проект распространяется под лицензией, указанной в файле [LICENSE](LICENSE).

## Авторы

- Оригинал: awa
- Порт на CMake/wxWidgets: [ваше имя]

## Ссылки

- [Infostart публикация](https://infostart.ru/1c/articles/2610907/)
- [Оригинальный репозиторий](https://github.com/fishca/v8_reader)
