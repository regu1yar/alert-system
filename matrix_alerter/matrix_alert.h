//
// Created by Мхитарян Нарек on 24/03/2020.
//

#ifndef MATRIX_ALERT_MATRIX_ALERT_H
#define MATRIX_ALERT_MATRIX_ALERT_H
#pragma once

#include <string>


class Basic_Alert
{
    std::string alert;
public:
    Basic_Alert(std::string s);
    std::string get_message();
    std::string get_room_id();
};

class Matrix_Alerter {
    std::string text;
    std::string token;
    std::string room_num;
public:
    Matrix_Alerter();
    void acquire_token();
    void get_room_num(std::string room_id);
    void reserve_token();
    bool send_alert(std::string message, std::string room_id);
    auto ret_token();
};

#endif //MATRIX_ALERT_MATRIX_ALERT_H
