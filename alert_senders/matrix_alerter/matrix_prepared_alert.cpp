//
// Created by Мхитарян Нарек on 14/04/2020.
//

#pragma once

#include "matrix_prepared_alert.h"

std::string MatrixPreparedAlert::getText() {
    return text_;
}

std::string MatrixPreparedAlert::getChatId() {
    return matrix_id_;
}

MatrixPreparedAlert::MatrixPreparedAlert(const std::string &chat_id,
                                         const std::string &text):
        matrix_id_(chat_id),
        text_(text){}