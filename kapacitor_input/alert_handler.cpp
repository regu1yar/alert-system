#include "alert_handler.h"

#include <exception>
#include <sstream>
#include <string>
#include <cpprest/filestream.h>
#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include <cpprest/uri.h>

void AlertHandler::handlePost(network::http_request message){
    auto alert_body_task = message.extract_json();

    alert_body_task.wait();
    web::json::value alert_body = alert_body_task.get();

    std::stringstream formatted;
    formatted << "Alert! Host/metric " << alert_body.at("id").as_string()
                                 << " at " << alert_body.at("time").as_string() << std::endl;
    try {
        //telegram.sendAlert(alert_body.get("chat_id").as_integer(), formatted.str());
        //TODO matrix.sendAlert();
        message.reply(web::http::status_codes::OK);
    } catch (std::exception) {
        message.reply(web::http::status_codes::ServiceUnavailable);
    }
}

