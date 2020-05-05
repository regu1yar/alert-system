#include <telegram_prepared_alert.h>

std::string TelegramPreparedAlert::getText() {
  return text_;
}

std::string TelegramPreparedAlert::getChatId() {
  return chat_id_;
}

TelegramPreparedAlert::TelegramPreparedAlert(std::string chat_id,
                                             const std::string& text):
        chat_id_(chat_id),
        text_(text){}
