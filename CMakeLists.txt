cmake_minimum_required(VERSION 3.10)
project(MyWxWidgetsApp VERSION 1.0 LANGUAGES CXX)

# Установите стандарт C++ (C++17)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Поиск wxWidgets
# wxWidgets должен быть установлен в системе
# Для Ubuntu/Debian: sudo apt-get install libwxgtk3.0-gtk3-dev
# Для Fedora: sudo dnf install wxGTK3-devel
# Для macOS с Homebrew: brew install wxwidgets
find_package(wxWidgets REQUIRED COMPONENTS core base)

# Если wxWidgets найден, добавляем его конфигурацию
if(wxWidgets_FOUND)
    include(${wxWidgets_USE_FILE})
    message(STATUS "wxWidgets found: ${wxWidgets_LIBRARIES}")
else()
    message(FATAL_ERROR "wxWidgets not found!")
endif()

# Добавьте исходные файлы вашего проекта
# Замените на ваши реальные файлы
set(SOURCES
    main.cpp
    # добавьте другие .cpp файлы здесь
)

set(HEADERS
    main.h
    # добавьте другие .h файлы здесь
)

# Создайте исполняемый файл
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Свяжите библиотеки wxWidgets с вашим проектом
target_link_libraries(${PROJECT_NAME} PRIVATE ${wxWidgets_LIBRARIES})

# Добавьте директории с заголовочными файлами
target_include_directories(${PROJECT_NAME} PRIVATE ${wxWidgets_INCLUDE_DIRS})

# Опционально: установка целевого файла
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

# Опционально: определение типа сборки (Debug/Release)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
