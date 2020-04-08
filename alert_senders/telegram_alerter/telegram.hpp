#pragma once

#include <string>
#include <cpprest/filestream.h>
#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include <cpprest/uri.h>
#include "abstract_sender.hpp"

using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;

class Alert{
public:
    std::string chat_id;
    std::string text;
};

class TelegramPreparedAlert: public PreparedAlert{
public:
    TelegramPreparedAlert(std::string chat_id, std::string text);
    std::string getChatId();
    std::string getText();
private:
    std::string chat_id_;
    std::string text_;
};

class TelegramSender: public Sender{
public:
    TelegramSender(std::string token): token_(token) {};
    TelegramSender(){};
    void setToken(std::string token);
    const std::string& getToken() const;
    void send(std::shared_ptr<PreparedAlert> prepared_alert) override;
private:
    void request();
    pplx::task<http_response> makeRequest(std::shared_ptr<TelegramPreparedAlert> telegram_alert);
    pplx::task<json::value> getResponse(http_response response);
private:
    std::string token_ = "1011512469:AAF28pOATldHJhuZBGV14ehNhBFeZVVw86w";
};


class TelegramPreparer: public Preparer{
public:
    TelegramPreparer(){};
    std::shared_ptr<PreparedAlert> prepare(Alert alert) override;
};


class TelegramFactory: public Factory{
public:
    TelegramFactory();
    std::shared_ptr<Sender> createSender() override;
    std::shared_ptr<Preparer> createPreparer() override;
};
