#include <iostream>
#include <ctime>
#include <thread>
#include <string>
#include <getopt.h>
#include "telegram.h"
#include "logger.h"
#include "config.h"
#include "emoji.h" // взято https://github.com/99x/emojicpp

using namespace std::chrono_literals;

// Глобальная переменная для хранения пользовательского сообщения
std::string customMessage = "Тестовое сообщение";
std::string chatId;

// Функция для отправки сообщения
void sendmessage() {
    Logger::info("Начало работы бота, отправка сообщения");
    
    // Создаем экземпляр бота
    TelegramBot bot(Config::TELEGRAM_TOKEN.c_str());
    
    // Формируем сообщение с эмодзи
    std::string message = emojicpp::emojize(":bangbang:" + customMessage + ":bangbang: :smile: \n");
    message += emojicpp::emojize(":dragon: :smile: \n"); 

    // Используем chatId из аргумента командной строки, если он задан, иначе из конфига
    std::string targetId = chatId.empty() ? Config::ID : chatId;

    // Отправляем сообщение
    if (bot.send_message(targetId.c_str(), message)) {
        Logger::info("Отправлено сообщение в группу ID: " + targetId);
    } else {
        Logger::error("Ошибка при отправке сообщения в группу");
    }
}

void printUsage(const char* programName) {
    std::cout << "Использование: " << programName << " [опции]\n"
              << "Опции:\n"
              << "  -l, --log <файл>   Путь к лог-файлу\n"
              << "  -c, --conf <файл>  Путь к конфигурационному файлу\n"
              << "  -m, --msg <текст> Пользовательское сообщение\n"
              << "  -i, --id <CHAT_ID> ID чата для отправки сообщения\n"
              << "  -h, --help         Показать эту справку\n";
}

int main(int argc, char* argv[]) {
    std::string logFile = "/var/log/telegram_bot.log";
    std::string configFile = "config.ini";

    static struct option long_options[] = {
        {"log", required_argument, 0, 'l'},
        {"conf", required_argument, 0, 'c'},
        {"msg", required_argument, 0, 'm'},
        {"id", required_argument, 0, 'i'},
        {"help", no_argument, 0, 'h'},
        {0, 0, 0, 0}
    };

    int opt;
    int option_index = 0;
    while ((opt = getopt_long(argc, argv, "l:c:m:i:h", long_options, &option_index)) != -1) {
        switch (opt) {
            case 'l':
                logFile = optarg;
                break;
            case 'c':
                configFile = optarg;
                break;
            case 'm':
                customMessage = optarg;
                break;
            case 'i':
                chatId = optarg;
                break;
            case 'h':
                printUsage(argv[0]);
                return 0;
            default:
                printUsage(argv[0]);
                return 1;
        }
    }

    // Загружаем конфигурацию из файла
    if (!Config::load(configFile.c_str())) {
        std::cerr << "Ошибка при загрузке конфигурационного файла: " << configFile << std::endl;
        return 1;
    }
    
    // Инициализируем логгер
    Logger::init(logFile.c_str());
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