#include <alert.h>
#include "telegram_preparer.h"


std::shared_ptr<PreparedAlert> TelegramPreparer::prepare(Alert alert) {
  return std::make_shared<TelegramPreparedAlert>(alert.chat_id, alert.text);
}