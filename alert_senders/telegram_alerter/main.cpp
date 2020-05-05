#include "alert.h"
#include "telegram_factory.h"

int main() {
  TelegramFactory factory;
  auto preparer = factory.createPreparer();
  auto sender = factory.createSender();
  Alert alert;
  alert.chat_id = "495925142";
  alert.text = "Privet";
  auto prepared_alert = preparer->prepare(alert);
  sender->send(prepared_alert);
  return 0;
}
