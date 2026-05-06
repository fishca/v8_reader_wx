cmake_minimum_required(VERSION 3.16)
project(v8_reader VERSION 1.0.0 LANGUAGES CXX C)

# ============================================================================
# Настройки проекта
# ============================================================================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Опции сборки
option(V8_READER_BUILD_GUI "Собрать GUI приложение на wxWidgets" ON)
option(V8_READER_BUILD_CLI "Собрать консольное приложение" OFF)
option(V8_READER_BUILD_TESTS "Собрать тесты" OFF)

# Имя исполняемого файла
set(V8_READER_GUI_NAME "v8_reader_wx")

# Пути
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# ============================================================================
# Исходные файлы библиотеки
# ============================================================================
file(GLOB V8_READER_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

file(GLOB V8_READER_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
)

# Исходные файлы zlib для статической компиляции
file(GLOB ZLIB_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/zlib/*.c"
)

file(GLOB ZLIB_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/zlib/*.h"
)

# ============================================================================
# Статическая библиотека zlib (встроенная)
# ============================================================================
# Автоматическое клонирование zlib если директория пуста
if(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/zlib/CMakeLists.txt")
    message(STATUS "zlib not found, cloning repository...")
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E rm -rf "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/zlib"
    )
    execute_process(
        COMMAND git clone --depth 1 https://github.com/madler/zlib.git "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/zlib"
        RESULT_VARIABLE GIT_CLONE_RESULT
    )
    if(NOT GIT_CLONE_RESULT EQUAL 0)
        message(FATAL_ERROR "Failed to clone zlib repository")
    endif()
endif()

# Используем родную систему сборки zlib через подкаталог
# Для Windows важно собрать именно статическую библиотеку zlibstatic.lib
set(ZLIB_BUILD_STATIC ON CACHE BOOL "Build static library" FORCE)
set(ZLIB_BUILD_SHARED OFF CACHE BOOL "Build shared library" FORCE)
set(SKIP_INSTALL_ALL ON CACHE BOOL "Skip installation" FORCE)
set(ZLIB_BUILD_EXAMPLES OFF CACHE BOOL "Disable examples" FORCE)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/zlib ${CMAKE_CURRENT_BINARY_DIR}/zlib_build)

# Создаём алиас для совместимости с остальным кодом
if(TARGET zlibstatic)
    add_library(zlib_static ALIAS zlibstatic)
    # Настройки для Windows -确保生成 zlibstatic.lib
    if(MSVC)
        set_target_properties(zlibstatic PROPERTIES
            OUTPUT_NAME "zlibstatic"
            DEBUG_POSTFIX "d"
        )
    endif()
    set_target_properties(zlibstatic PROPERTIES
        POSITION_INDEPENDENT_CODE ON
    )
elseif(TARGET zlib)
    # Если zlibstatic не создана, используем zlib как статическую
    message(WARNING "zlibstatic не найдена, используем zlib")
    add_library(zlib_static ALIAS zlib)
endif()

# ============================================================================
# Статическая библиотека v8_reader_lib
# ============================================================================
add_library(v8_reader_lib STATIC
    ${V8_READER_SOURCES}
    ${V8_READER_HEADERS}
)

target_include_directories(v8_reader_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty
)

# Линкуем встроенную zlib
target_link_libraries(v8_reader_lib PUBLIC zlib_static)

# Требования к компилятору
target_compile_features(v8_reader_lib PUBLIC cxx_std_17)

# Платформенные настройки
if(WIN32)
    target_compile_definitions(v8_reader_lib PRIVATE _WINDOWS UNICODE _UNICODE)
endif()

# ============================================================================
# wxWidgets для GUI приложения
# ============================================================================
if(V8_READER_BUILD_GUI)
    find_package(wxWidgets COMPONENTS core base REQUIRED)
    
    if(wxWidgets_FOUND)
        include(${wxWidgets_USE_FILE})
        
        # Исходные файлы GUI приложения
        file(GLOB GUI_SOURCES
            "${CMAKE_CURRENT_SOURCE_DIR}/apps/gui/*.cpp"
        )
        
        file(GLOB GUI_HEADERS
            "${CMAKE_CURRENT_SOURCE_DIR}/apps/gui/*.h"
        )
        
        add_executable(v8_reader_wx
            ${GUI_SOURCES}
            ${GUI_HEADERS}
        )
        
        target_link_libraries(v8_reader_wx
            PRIVATE
                v8_reader_lib
                ${wxWidgets_LIBRARIES}
        )
        
        target_include_directories(v8_reader_wx PRIVATE
            ${wxWidgets_INCLUDE_DIRS}
        )
        
        target_compile_definitions(v8_reader_wx PRIVATE
            ${wxWidgets_DEFINITIONS}
        )
        
        set_target_properties(v8_reader_wx PROPERTIES
            WIN32_EXECUTABLE TRUE  # Для Windows создаёт GUI приложение без консоли
            OUTPUT_NAME "${V8_READER_GUI_NAME}"  # Имя исполняемого файла
        )
    else()
        message(FATAL_ERROR "wxWidgets не найден. Отключите V8_READER_BUILD_GUI или установите wxWidgets.")
    endif()
endif()

# ============================================================================
# Консольное приложение (CLI)
# ============================================================================
if(V8_READER_BUILD_CLI)
    # Исходные файлы CLI приложения
    file(GLOB CLI_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/apps/cli/*.cpp"
    )
    
    file(GLOB CLI_HEADERS
        "${CMAKE_CURRENT_SOURCE_DIR}/apps/cli/*.h"
    )
    
    # Если нет файлов CLI, создаём минимальный main.cpp
    if(NOT CLI_SOURCES)
        set(CLI_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/apps/cli/main.cpp")
        file(WRITE ${CLI_SOURCES} 
"#include <iostream>
#include \"APIcfBase.h\"

int main(int argc, char* argv[]) {
    std::cout << \"v8_reader CLI - Чтение конфигураций 1С\" << std::endl;
    std::cout << \"Версия: ${PROJECT_VERSION}\" << std::endl;
    
    if (argc > 1) {
        std::cout << \"Обработка файла: \" << argv[1] << std::endl;
        // Здесь будет логика обработки файлов 1С
    } else {
        std::cout << \"Использование: v8_reader_cli <файл.cf/.cfu/.cfe>\" << std::endl;
    }
    
    return 0;
}
")
    endif()
    
    add_executable(v8_reader_cli
        ${CLI_SOURCES}
        ${CLI_HEADERS}
    )
    
    target_link_libraries(v8_reader_cli
        PRIVATE
            v8_reader_lib
    )
endif()

# ============================================================================
# Тесты
# ============================================================================
if(V8_READER_BUILD_TESTS)
    enable_testing()
    
    file(GLOB TEST_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/tests/*.cpp"
    )
    
    if(TEST_SOURCES)
        add_executable(v8_reader_tests
            ${TEST_SOURCES}
        )
        
        target_link_libraries(v8_reader_tests
            PRIVATE
                v8_reader_lib
        )
        
        add_test(NAME v8_reader_tests COMMAND v8_reader_tests)
    endif()
endif()

# ============================================================================
# Установка
# ============================================================================
install(TARGETS v8_reader_lib
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)

if(V8_READER_BUILD_GUI)
    install(TARGETS v8_reader_wx
        RUNTIME DESTINATION bin
    )
endif()

if(V8_READER_BUILD_CLI)
    install(TARGETS v8_reader_cli
        RUNTIME DESTINATION bin
    )
endif()

install(DIRECTORY src/ DESTINATION include/v8_reader FILES_MATCHING PATTERN "*.h")

# ============================================================================
# Информация о проекте
# ============================================================================
message(STATUS "===========================================")
message(STATUS "v8_reader конфигурация сборки:")
message(STATUS "  Версия: ${PROJECT_VERSION}")
message(STATUS "  Стандарт C++: ${CMAKE_CXX_STANDARD}")
message(STATUS "  GUI приложение: ${V8_READER_BUILD_GUI} (имя: ${V8_READER_GUI_NAME})")
message(STATUS "  CLI приложение: ${V8_READER_BUILD_CLI}")
message(STATUS "  Тесты: ${V8_READER_BUILD_TESTS}")
message(STATUS "===========================================")
