#pragma once

#include <abstract_sender.h>
#include <string>

class TelegramPreparedAlert: public PreparedAlert {
public:
    TelegramPreparedAlert(std::string chat_id, const std::string& text);

    std::string getChatId();

    std::string getText();

private:
    std::string chat_id_;
    std::string text_;
};