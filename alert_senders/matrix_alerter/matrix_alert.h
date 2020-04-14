//
// Created by Мхитарян Нарек on 24/03/2020.
//
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


class Alert
{
public:
    std::string text;
    std::string chat_id;
};

class MatrixPreparedAlert : public PreparedAlert
{
public:
    MatrixPreparedAlert(std::string matrix_id, std::string text);
    std::string getChatId();
    std::string getText();
private:
    std::string matrix_id_;
    std::string text_;
};

class MatrixSender: public Sender {
public:
    MatrixSender(std::string token) : token_(token) {};

    MatrixSender() {};

    void setToken(std::string token);

    const std::string &getToken() const;

    void send(std::shared_ptr<PreparedAlert> prepared_alert) override;

    void acquireToken();

private:
    void reserveToken();

    std::string token_ = "MDAxOGxvY2F0aW9uIG1hdHJpeC5vcmcKMDAxM2lkZW50aWZpZXIga2V5CjAwMTBjaWQgZ2VuID0gMQowMDI3Y2lkIHVzZXJfaWQgPSBAbmFyZWtpdG86bWF0cml4Lm9yZwowMDE2Y2lkIHR5cGUgPSBhY2Nlc3MKMDAyMWNpZCBub25jZSA9ICprVTp2cioyaUp1K1hTeDQKMDAyZnNpZ25hdHVyZSAltUACVTRGjM8oXfARpzoClL158YfFM4q6AfisXGOa9Qo";
};

class MatrixPreparer: public Preparer{
public:
    MatrixPreparer(){};
    std::shared_ptr<PreparedAlert> prepare(Alert alert) override;
};

class MatrixFactory: public Factory{
public:
    MatrixFactory();
    std::shared_ptr<Sender> createSender() override;
    std::shared_ptr<Preparer> createPreparer() override;
};
