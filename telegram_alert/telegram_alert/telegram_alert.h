#pragma once

#include <string>

class TelegramAlert {
public:
    TelegramAlert(std::string token): token_(token) {}
    void sendAlert(uint64_t chat_id, std::string text);
private:
    std::string token_;
};


