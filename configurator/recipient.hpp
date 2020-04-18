#pragma once

#include <cpprest/json.h>
#include <string>

class Recipient {
public:
  explicit Recipient(const std::string & name, const std::string & telegram_chat_id);
  explicit Recipient(const web::json::value & recipient_json);
  std::string getName();
  std::string getTelegramChatId();

private:
  std::string name_;
  std::string telegram_chat_id_;
};