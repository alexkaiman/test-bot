#include <iostream>
#include <ctime>
#include <thread>
#include "telegram.h"
#include "logger.h"
#include "config.h"
#include "emoji.h" // взято https://github.com/99x/emojicpp

using namespace std::chrono_literals;

// Функция для отправки сообщения
void sendmessage() {
    Logger::info("Начало работы бота, отправка сообщения");
    
    // Создаем экземпляр бота
    TelegramBot bot(Config::TELEGRAM_TOKEN.c_str());
    
    // Формируем сообщение с эмодзи
    std::string message = emojicpp::emojize(":bangbang:Тестовое сообщение:bangbang: :smile: \n");
    message += emojicpp::emojize(":dragon: :smile: \n"); 

    // Отправляем сообщение
    if (bot.send_message(Config::ID.c_str(), message)) {
        Logger::info("Отправлено сообщение в группу ID: "+Config::ID);
    } else {
        Logger::error("Ошибка при отправке сообщения в группу");
    }
}

int main() {
    // Загружаем конфигурацию из файла config.ini
    if (!Config::load("config.ini")) {
        return 1;
    }
    
    // Инициализируем логгер, не забываем про права на telegram_bot.log
    Logger::init("/var/log/telegram_bot.log");
    Logger::info("Бот запускается");

    try {
        // Отправляем сообщение
        sendmessage();
        Logger::info("Бот завершил работу");
    } catch (const std::exception& e) {
        Logger::error("Критическая ошибка при выполнении бота: " + std::string(e.what()));
    }

    return 0;
}