#include "alert_handler.h"

#include <exception>
#include <sstream>
#include <string>
#include <cpprest/filestream.h>
#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include <cpprest/uri.h>
#include <matrix_alerter/matrix_factory.h>
//#include <alert.h>
#include "alert.pb.h"
#include <telegram_alerter/telegram_factory.h>
#include "abstract_sender.h"

void AlertHandler::handlePost(network::http_request message) {
  auto alert_body_task = message.extract_json();

  std::cout << "New Request!" << std::endl;

  alert_body_task.wait();
  web::json::value alert_body = alert_body_task.get();

  std::stringstream formatted;
  formatted << "Alert! Host/metric " << alert_body.at("id").as_string()
            << " at " << alert_body.at("time").as_string() << std::endl;
  try {
    std::shared_ptr<Factory> factory;
    Alert alert;
    if (alert_body.has_field("matrix_id")) {
      factory = std::shared_ptr<MatrixFactory>(new MatrixFactory());
      alert.set_chat_id(alert_body.at("matrix_id").as_string());
      std::cout << "Going to Matrix" << std::endl;
    } else if (alert_body.has_field("chat_id")) {
      factory = std::shared_ptr<TelegramFactory>(new TelegramFactory());
      alert.set_chat_id(alert_body.at("chat_id").as_string());
      std::cout << "Going to Telegram" << std::endl;
    } else {
      // ONLY FOR TESTING PURPOSES. TEST + KAPACITOR
      factory = std::shared_ptr<MatrixFactory>(new MatrixFactory());
      alert.set_chat_id("!peaLsZdtyOLKogIHZJ:matrix.org");
      std::cout << "Going to Matrix" << std::endl;
    }
    auto preparer = factory->createPreparer();
    auto sender = factory->createSender();
    alert.set_text(formatted.str());
    auto prepared_alert = preparer->prepare(alert);
    sender->send(prepared_alert);
    std::cout << "SENT!" << std::endl;
    message.reply(web::http::status_codes::OK);

  } catch (std::exception) {
    message.reply(web::http::status_codes::ServiceUnavailable);
  }
}
