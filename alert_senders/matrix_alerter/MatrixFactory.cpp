//
// Created by Мхитарян Нарек on 14/04/2020.
//

#pragma once

#include "MatrixFactory.h"
#include "MatrixPreparer.h"
#include "MatrixSender.h"


MatrixFactory::MatrixFactory() {}

std::shared_ptr<Sender> MatrixFactory::createSender() {
    return std::make_shared<MatrixSender>();
}

std::shared_ptr<Preparer> MatrixFactory::createPreparer() {
    return std::make_shared<MatrixPreparer>();
}
