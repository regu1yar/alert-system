//
// Created by Мхитарян Нарек on 14/04/2020.
//

#pragma once

#include "abstract_sender.hpp"


#ifndef ALERT_SYSTEM_MATRIXPREPARER_H
#define ALERT_SYSTEM_MATRIXPREPARER_H
class MatrixPreparer: public Preparer{
public:
    MatrixPreparer(){};
    std::shared_ptr<PreparedAlert> prepare(Alert alert) override;
};
#endif //ALERT_SYSTEM_MATRIXPREPARER_H
