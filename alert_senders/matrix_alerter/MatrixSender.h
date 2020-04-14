//
// Created by Мхитарян Нарек on 14/04/2020.
//

#pragma once

#ifndef ALERT_SYSTEM_MATRIXSENDER_H
#define ALERT_SYSTEM_MATRIXSENDER_H
#include <string>
#include "abstract_sender.hpp"

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

#endif //ALERT_SYSTEM_MATRIXSENDER_H
