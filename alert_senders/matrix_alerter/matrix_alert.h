//
// Created by Мхитарян Нарек on 24/03/2020.
//
#pragma once

#include <string>


class BasicAlert
{
    std::string alert;
public:
    BasicAlert(std::string s);
    std::string getMessage();
    std::string getRoomId();
};

class MatrixAlerter {
    std::string text;
    std::string token;
    std::string room_num;
public:
    MatrixAlerter();
    void acquireToken();
    void getRoomNum(std::string room_id);
    void reserveToken();
    bool sendAlert(std::string message, std::string room_id);
    auto retToken();
};