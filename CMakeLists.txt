cmake_minimum_required(VERSION 3.16)
project(v8_reader VERSION 1.0.0 LANGUAGES CXX)

# ============================================================================
# Настройки проекта
# ============================================================================
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Опции сборки
option(V8_READER_BUILD_GUI "Собрать GUI приложение на wxWidgets" ON)
option(V8_READER_BUILD_CLI "Собрать консольное приложение" ON)
option(V8_READER_BUILD_TESTS "Собрать тесты" OFF)

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

# Файлы zlib (только заголовки, реализация линкуется из системы)
file(GLOB ZLIB_HEADERS
    "${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/zlib/*.h"
)

# ============================================================================
# Статическая библиотека v8_reader_lib
# ============================================================================
add_library(v8_reader_lib STATIC
    ${V8_READER_SOURCES}
    ${V8_READER_HEADERS}
    ${ZLIB_HEADERS}
)

target_include_directories(v8_reader_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty
)

# Требования к компилятору
target_compile_features(v8_reader_lib PUBLIC cxx_std_17)

# Платформенные настройки
if(WIN32)
    target_compile_definitions(v8_reader_lib PRIVATE _WINDOWS UNICODE _UNICODE)
    # На Windows может потребоваться системная zlib
    find_package(ZLIB QUIET)
    if(ZLIB_FOUND)
        target_link_libraries(v8_reader_lib PUBLIC ZLIB::ZLIB)
        target_include_directories(v8_reader_lib PRIVATE ${ZLIB_INCLUDE_DIRS})
    else()
        message(WARNING "ZLIB не найден. Некоторые функции могут быть недоступны.")
    endif()
else()
    # На Linux/macOS используем системную zlib
    find_package(ZLIB REQUIRED)
    target_link_libraries(v8_reader_lib PUBLIC ZLIB::ZLIB)
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
        
        add_executable(v8_reader_gui
            ${GUI_SOURCES}
            ${GUI_HEADERS}
        )
        
        target_link_libraries(v8_reader_gui
            PRIVATE
                v8_reader_lib
                ${wxWidgets_LIBRARIES}
        )
        
        target_include_directories(v8_reader_gui PRIVATE
            ${wxWidgets_INCLUDE_DIRS}
        )
        
        target_compile_definitions(v8_reader_gui PRIVATE
            ${wxWidgets_DEFINITIONS}
        )
        
        set_target_properties(v8_reader_gui PROPERTIES
            WIN32_EXECUTABLE TRUE  # Для Windows создаёт GUI приложение без консоли
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
    install(TARGETS v8_reader_gui
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
message(STATUS "  GUI приложение: ${V8_READER_BUILD_GUI}")
message(STATUS "  CLI приложение: ${V8_READER_BUILD_CLI}")
message(STATUS "  Тесты: ${V8_READER_BUILD_TESTS}")
message(STATUS "===========================================")
