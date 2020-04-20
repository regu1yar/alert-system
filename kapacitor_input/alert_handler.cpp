#include "alert_handler.h"

#include <exception>
#include <sstream>
#include <string>
#include <cpprest/filestream.h>
#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include <cpprest/uri.h>
#include <matrix_alerter/matrix_factory.h>
#include <alert.h>
#include <telegram_alerter/telegram.hpp>
#include "abstract_sender.hpp"

void AlertHandler::handlePost(network::http_request message){
    auto alert_body_task = message.extract_json();

    alert_body_task.wait();
    web::json::value alert_body = alert_body_task.get();

    std::stringstream formatted;
    formatted << "Alert! Host/metric " << alert_body.at("id").as_string()
                                 << " at " << alert_body.at("time").as_string() << std::endl;
    try {
        std::shared_ptr <Factory> factory;
        Alert alert;
        if(alert_body.has_field("matrix_id")) {
            factory = std::shared_ptr<MatrixFactory>(new MatrixFactory());
            alert.chat_id = alert_body.at("matrix_id").as_string();
        }
        else if(alert_body.has_field("chat_id")) {
            factory = std::shared_ptr<TelegramFactory>(new TelegramFactory());
            alert.chat_id = alert_body.at("chat_id").as_string();
        }
        auto preparer = factory->createPreparer();
        auto sender = factory->createSender();
        alert.text = formatted.str();
        auto prepared_alert = preparer->prepare(alert);
        sender->send(prepared_alert);
        message.reply(web::http::status_codes::OK);

    } catch (std::exception) {
        message.reply(web::http::status_codes::ServiceUnavailable);
    }
}
