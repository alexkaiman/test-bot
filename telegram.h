#pragma once
#include <string>
#include <curl/curl.h>

class TelegramBot {
public:
    // Конструктор, принимающий токен бота
    TelegramBot(const std::string& token);
    
    // Деструктор для освобождения ресурсов CURL
    ~TelegramBot();
    
    // Метод для отправки сообщения
    bool send_message(const std::string& chat_id, const std::string& message);
private:
    std::string m_token;
    CURL* curl;
    
    // Статический метод обратного вызова для CURL
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s);
};