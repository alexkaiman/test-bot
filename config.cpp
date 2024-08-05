#include "config.h"
#include <ini.h>
#include "logger.h"
#include <cstring>

// Статические переменные класса Config
std::string Config::TELEGRAM_TOKEN;
std::string Config::ID;

// Обработчик для парсинга INI файла
static int handler(void* user, const char* section, const char* name, const char* value) {
    // Проверяем, что секция - "Telegram"
    if (strcmp(section, "Telegram") == 0) {
        // Заполняем соответствующие поля класса Config
        if (strcmp(name, "TOKEN") == 0) Config::TELEGRAM_TOKEN = value;
        else if (strcmp(name, "ID") == 0) Config::ID = value;
    } 
    return 1;
}

// Загрузка конфигурации из файла
bool Config::load(const std::string& filename) {
    // Используем библиотеку inih для парсинга INI файла
    if (ini_parse(filename.c_str(), handler, nullptr) < 0) {
        Logger::error("Не удалось загрузить конфигурационный файл: " + filename);
        return false;
    }
    Logger::info("Конфигурационный файл успешно загружен: " + filename);
    return true;
}