#pragma once

#include "abstract_sender.h"
#include <telegram_sender.h>
#include <telegram_preparer.h>

class TelegramFactory: public Factory {
public:
    TelegramFactory();

    std::shared_ptr<Sender> createSender() override;

    std::shared_ptr<Preparer> createPreparer() override;
};
