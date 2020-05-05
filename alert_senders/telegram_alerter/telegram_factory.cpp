#include <telegram_factory.h>

TelegramFactory::TelegramFactory() {}

std::shared_ptr<Sender> TelegramFactory::createSender() {
  return std::make_shared<TelegramSender>();
}

std::shared_ptr<Preparer> TelegramFactory::createPreparer() {
  return std::make_shared<TelegramPreparer>();
}
