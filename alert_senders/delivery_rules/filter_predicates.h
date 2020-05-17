#pragma once

#include <string>

#include "alert.pb.h"

class FilterPredicate {
 public:
  virtual ~FilterPredicate() = 0;

  virtual bool isTrue(const alert::Alert& alert) const = 0;
};
