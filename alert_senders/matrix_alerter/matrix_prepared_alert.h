//
// Created by Мхитарян Нарек on 14/04/2020.
//

#pragma once

#include "abstract_sender.hpp"
#include <string>

class MatrixPreparedAlert : public PreparedAlert
{
public:
    MatrixPreparedAlert(const std::string &matrix_id, const std::string &text);
    std::string getChatId();
    std::string getText();
private:
    std::string matrix_id_;
    std::string text_;
};

