//
// Created by Мхитарян Нарек on 14/04/2020.
//


#pragma once
#include "Alert.h"
#include "MatrixPreparedAlert.h"
#include "MatrixPreparer.h"


std::shared_ptr<PreparedAlert> MatrixPreparer::prepare(Alert alert) {
    return std::make_shared<MatrixPreparedAlert>(alert.chat_id, alert.text);
}