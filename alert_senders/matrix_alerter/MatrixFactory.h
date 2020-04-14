//
// Created by Мхитарян Нарек on 14/04/2020.
//

#pragma once
#include "abstract_sender.hpp"

#ifndef ALERT_SYSTEM_MATRIXFACTORY_H
#define ALERT_SYSTEM_MATRIXFACTORY_H

class MatrixFactory: public Factory{
public:
    MatrixFactory();
    std::shared_ptr<Sender> createSender() override;
    std::shared_ptr<Preparer> createPreparer() override;
};

#endif //ALERT_SYSTEM_MATRIXFACTORY_H
