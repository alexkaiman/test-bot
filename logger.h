#pragma once
#include <string>

class Logger {
public:
    // Инициализация логгера с указанием файла для записи логов
    static void init(const std::string& filename);
    
    // Запись информационного сообщения
    static void info(const std::string& message);
    
    // Запись сообщения об ошибке
    static void error(const std::string& message);
private:
    // Внутренний метод для записи лога
    static void log(const std::string& level, const std::string& message);
};