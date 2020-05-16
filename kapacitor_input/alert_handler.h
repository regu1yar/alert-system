#pragma once

#include "alert_parser.h"
#include "handler.h"
#include "router_controller.h"

class AlertHandler : public network::Handler {
 public:
  void handlePost(network::http_request message) override;

 private:
  AlertParser parser_;
};
