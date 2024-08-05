#pragma once
#include <string>

class Config {
public:
    // Загружает конфигурацию из файла
    static bool load(const std::string& filename);
    
    // Токен для доступа к API Telegram
    static std::string TELEGRAM_TOKEN;
    
    // ID чата или группы для отправки сообщений
    static std::string ID;
};