//
// Created by Мхитарян Нарек on 14/04/2020.
//

#pragma once

#include "MatrixPreparedAlert.h"

std::string MatrixPreparedAlert::getText() {
    return text_;
}

std::string MatrixPreparedAlert::getChatId() {
    return matrix_id_;
}

MatrixPreparedAlert::MatrixPreparedAlert(std::string chat_id,
                                         std::string text):
        matrix_id_(chat_id),
        text_(text){}