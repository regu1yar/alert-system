#include <exception>
#include <memory>
#include <sstream>

#include <cpprest/http_client.h>
#include <cpprest/json.h>

#include "alert_handler.h"
#include "alert.pb.h"
#include <matrix_alerter/matrix_factory.h>
#include <telegram_alerter/telegram_factory.h>
#include "abstract_sender.h"

void AlertHandler::handlePost(network::http_request message) {
  auto alert_body_task = message.extract_json();

  std::cerr << "New Request!" << std::endl;

  alert_body_task.wait();
  web::json::value alert_body = alert_body_task.get();

  try {
    alert::Alert alert = parser_.parseJson(alert_body);

    // ONLY FOR TESTING PURPOSES. TEST + KAPACITOR
    std::shared_ptr<Factory> factory = std::make_shared<MatrixFactory>();
    auto preparer = factory->createPreparer();
    auto sender = factory->createSender("!peaLsZdtyOLKogIHZJ:matrix.org");
    auto prepared_alert = preparer->prepare(alert);
    sender->send(prepared_alert);

    std::cerr << "SENT!" << std::endl;
    message.reply(web::http::status_codes::OK);
  } catch (std::exception) {
    message.reply(web::http::status_codes::ServiceUnavailable);
  }
}
