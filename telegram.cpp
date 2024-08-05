#include "telegram.h"
#include "logger.h"
#include <sstream>

// Конструктор
TelegramBot::TelegramBot(const std::string& token) : m_token(token), curl(nullptr) {
    curl = curl_easy_init();
    if (!curl) {
        Logger::error("Не удалось инициализировать CURL");
    }
}

// Деструктор
TelegramBot::~TelegramBot() {
    if (curl) {
        curl_easy_cleanup(curl);
    }
}

// Метод отправки сообщения
bool TelegramBot::send_message(const std::string& chat_id, const std::string& message) {
    if (!curl) {
        Logger::error("CURL не инициализирован");
        return false;
    }

    // Формируем URL и параметры запроса
    std::string url = "https://api.telegram.org/bot" + m_token + "/sendMessage";
    std::string post_fields = "chat_id=" + chat_id + "&text=" + curl_easy_escape(curl, message.c_str(), message.length());

    // Настраиваем CURL
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_fields.c_str());

    std::string response;
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

    // Выполняем запрос
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        Logger::error("Ошибка отправки сообщения: " + std::string(curl_easy_strerror(res)));
        return false;
    }

    Logger::info("Сообщение успешно отправлено");
    return true;
}

// Статический метод обратного вызова для CURL
size_t TelegramBot::WriteCallback(void* contents, size_t size, size_t nmemb, std::string* s) {
    size_t newLength = size * nmemb;
    try {
        s->append((char*)contents, newLength);
    } catch (std::bad_alloc& e) {
        return 0;
    }
    return newLength;
}