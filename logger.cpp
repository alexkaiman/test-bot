#include "logger.h"
#include <fstream>
#include <ctime>
#include <chrono> 
#include <iomanip>

// Статический файловый поток для записи логов
static std::ofstream log_file;

// Инициализация логгера
void Logger::init(const std::string& filename) {
    log_file.open(filename, std::ios::app);
}

// Запись информационного сообщения
void Logger::info(const std::string& message) {
    log("INFO", message);
}

// Запись сообщения об ошибке
void Logger::error(const std::string& message) {
    log("ERROR", message);
}

// Внутренний метод для записи лога
void Logger::log(const std::string& level, const std::string& message) {
    // Получаем текущее время
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    // Форматируем и записываем лог
    log_file << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X") 
             << " - " << level << " - " << message << std::endl;
}