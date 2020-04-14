//
// Created by Мхитарян Нарек on 14/04/2020.
//

#pragma once

#include "matrix_factory.h"
#include "matrix_preparer.h"
#include "matrix_sender.h"


MatrixFactory::MatrixFactory() {}

std::shared_ptr<Sender> MatrixFactory::createSender() {
    return std::make_shared<MatrixSender>();
}

std::shared_ptr<Preparer> MatrixFactory::createPreparer() {
    return std::make_shared<MatrixPreparer>();
}
