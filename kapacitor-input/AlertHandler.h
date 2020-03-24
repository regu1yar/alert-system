#pragma once
//#include "TelegramAlert.h"
#include "handler.h"
#include "router_controller.h"

class AlertHandler : public network::Handler {
public:
    // /send_alert uri
    void handlePost(network::http_request message) override;

private:
    //TelegramAlert telegram;
    //void send();
};