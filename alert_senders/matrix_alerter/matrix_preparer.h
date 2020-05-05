//
// Created by Мхитарян Нарек on 14/04/2020.
//

#pragma once

#include "abstract_sender.h"

class MatrixPreparer: public Preparer{
public:
    MatrixPreparer(){};
    std::shared_ptr<PreparedAlert> prepare(Alert alert) override;
};
