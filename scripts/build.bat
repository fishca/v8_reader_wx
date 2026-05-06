@echo off
REM Скрипт для сборки проекта v8_reader на Windows

setlocal enabledelayedexpansion

set SCRIPT_DIR=%~dp0
set BUILD_DIR=%SCRIPT_DIR%build
set BUILD_TYPE=Release
set EXTRA_ARGS=

REM Парсинг аргументов
:parse_args
if "%1"=="" goto :end_parse
if "%1"=="--debug" (
    set BUILD_TYPE=Debug
    shift
    goto :parse_args
)
if "%1"=="--clean" (
    if exist "%BUILD_DIR%" rmdir /s /q "%BUILD_DIR%"
    echo Директория build удалена
    shift
    goto :parse_args
)
if "%1"=="--gui-only" (
    set EXTRA_ARGS=!EXTRA_ARGS! -DV8_READER_BUILD_CLI=OFF
    shift
    goto :parse_args
)
if "%1"=="--cli-only" (
    set EXTRA_ARGS=!EXTRA_ARGS! -DV8_READER_BUILD_GUI=OFF
    shift
    goto :parse_args
)
if "%1"=="--with-tests" (
    set EXTRA_ARGS=!EXTRA_ARGS! -DV8_READER_BUILD_TESTS=ON
    shift
    goto :parse_args
)
if "%1"=="--help" (
    echo Использование: %~nx0 [опции]
    echo.
    echo Опции:
    echo   --debug       Сборка в режиме отладки (по умолчанию Release)
    echo   --clean       Очистить директорию build перед сборкой
    echo   --gui-only    Собрать только GUI приложение
    echo   --cli-only    Собрать только CLI приложение
    echo   --with-tests  Собрать тесты
    echo   --help        Показать эту справку
    exit /b 0
)
echo Неизвестная опция: %1
echo Используйте --help для получения информации
exit /b 1

:end_parse
echo ============================================
echo Сборка v8_reader
echo Тип сборки: %BUILD_TYPE%
echo ============================================

REM Создание директории сборки
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
cd "%BUILD_DIR%"

REM Конфигурация CMake
echo Конфигурация CMake...
cmake .. ^
    -DCMAKE_BUILD_TYPE=%BUILD_TYPE% ^
    %EXTRA_ARGS%
if errorlevel 1 exit /b 1

REM Сборка
echo Сборка...
cmake --build . --config %BUILD_TYPE%
if errorlevel 1 exit /b 1

echo.
echo ============================================
echo Сборка завершена!
echo Бинарные файлы находятся в: %BUILD_DIR%\bin\
echo ============================================

REM Запуск тестов если они собраны
if "%EXTRA_ARGS%"=="%EXTRA_ARGS:-DV8_READER_BUILD_TESTS=ON=%" (
    goto :skip_tests
)
echo Запуск тестов...
ctest --test-dir . --build-config %BUILD_TYPE%

:skip_tests
endlocal
