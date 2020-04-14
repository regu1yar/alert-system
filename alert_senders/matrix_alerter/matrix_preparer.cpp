//
// Created by Мхитарян Нарек on 14/04/2020.
//


#pragma once
#include "alert.h"
#include "matrix_prepared_alert.h"
#include "matrix_preparer.h"


std::shared_ptr<PreparedAlert> MatrixPreparer::prepare(Alert alert) {
    return std::make_shared<MatrixPreparedAlert>(alert.chat_id, alert.text);
}