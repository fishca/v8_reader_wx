#include <iostream>
#include "APIcfBase.h"

int main(int argc, char* argv[]) {
    std::cout << "v8_reader CLI - Чтение конфигураций 1С" << std::endl;
    std::cout << "Версия: 1.0.0" << std::endl;
    
    if (argc > 1) {
        std::cout << "Обработка файла: " << argv[1] << std::endl;
        // Здесь будет логика обработки файлов 1С
    } else {
        std::cout << "Использование: v8_reader_cli <файл.cf/.cfu/.cfe>" << std::endl;
    }
    
    return 0;
}
