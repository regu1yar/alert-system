#pragma once

#include <memory>

class Alert;

class PreparedAlert{}; // virtual -> TelegramPreparedAlert, MatrixPreparedAlert...

class Sender {
public:
    virtual void send(std::shared_ptr<PreparedAlert> prepared_alert) = 0;
};

class Preparer {
public:
    virtual std::shared_ptr<PreparedAlert> prepare(Alert alert) = 0;
};

class Factory {
public:
    virtual std::shared_ptr<Sender> createSender() = 0;
    virtual std::shared_ptr<Preparer> createPreparer() = 0;
};