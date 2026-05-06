#!/bin/bash
# Скрипт для сборки проекта v8_reader

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="${SCRIPT_DIR}/build"
BUILD_TYPE="Release"

# Парсинг аргументов
while [[ $# -gt 0 ]]; do
    case $1 in
        --debug)
            BUILD_TYPE="Debug"
            shift
            ;;
        --clean)
            rm -rf "${BUILD_DIR}"
            echo "Директория build удалена"
            shift
            ;;
        --gui-only)
            EXTRA_ARGS="-DV8_READER_BUILD_CLI=OFF"
            shift
            ;;
        --cli-only)
            EXTRA_ARGS="-DV8_READER_BUILD_GUI=OFF"
            shift
            ;;
        --with-tests)
            EXTRA_ARGS="${EXTRA_ARGS} -DV8_READER_BUILD_TESTS=ON"
            shift
            ;;
        --help)
            echo "Использование: $0 [опции]"
            echo ""
            echo "Опции:"
            echo "  --debug       Сборка в режиме отладки (по умолчанию Release)"
            echo "  --clean       Очистить директорию build перед сборкой"
            echo "  --gui-only    Собрать только GUI приложение"
            echo "  --cli-only    Собрать только CLI приложение"
            echo "  --with-tests  Собрать тесты"
            echo "  --help        Показать эту справку"
            exit 0
            ;;
        *)
            echo "Неизвестная опция: $1"
            echo "Используйте --help для получения информации"
            exit 1
            ;;
    esac
done

echo "============================================"
echo "Сборка v8_reader"
echo "Тип сборки: ${BUILD_TYPE}"
echo "============================================"

# Создание директории сборки
mkdir -p "${BUILD_DIR}"
cd "${BUILD_DIR}"

# Конфигурация CMake
echo "Конфигурация CMake..."
cmake .. \
    -DCMAKE_BUILD_TYPE=${BUILD_TYPE} \
    ${EXTRA_ARGS:-}

# Сборка
echo "Сборка..."
cmake --build . --config ${BUILD_TYPE} -j$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)

echo ""
echo "============================================"
echo "Сборка завершена!"
echo "Бинарные файлы находятся в: ${BUILD_DIR}/bin/"
echo "============================================"

# Запуск тестов если они собраны
if [[ "${EXTRA_ARGS}" == *"V8_READER_BUILD_TESTS=ON"* ]]; then
    echo "Запуск тестов..."
    ctest --test-dir . --build-config ${BUILD_TYPE}
fi
