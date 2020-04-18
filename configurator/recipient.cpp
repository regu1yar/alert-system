#include "recipient.hpp"

Recipient::Recipient(const std::string & name, const std::string & telegram_chat_id)
  : name_(name)
  , telegram_chat_id_(telegram_chat_id)
  {}

Recipient::Recipient(const web::json::value & recipient_json) {
  web::json::object recipient = recipient_json.as_object();
  name_ = recipient["name"].as_string();
  telegram_chat_id_ = recipient["id_for_bot"].as_string();
}

std::string Recipient::getName() {
  return name_;
}

std::string Recipient::getTelegramChatId() {
  return telegram_chat_id_;
}
