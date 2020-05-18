#include <exception>
#include <memory>
#include <sstream>

#include <cpprest/http_client.h>
#include <cpprest/json.h>

#include "alert_handler.h"
#include "alert.pb.h"
#include <matrix_alerter/matrix_factory.h>
#include <telegram_alerter/telegram_factory.h>
#include <configurator_service.h>
#include "abstract_sender.h"

AlertHandler::AlertHandler(): factories_({{"matrix", std::make_shared<MatrixFactory>()},
                                          {"telegram", std::make_shared<TelegramFactory>()}})
                                          {}

void AlertHandler::handlePost(network::http_request message) {
  auto alert_body_task = message.extract_json();

  std::cerr << "New Request!" << std::endl;

  alert_body_task.wait();
  web::json::value alert_body = alert_body_task.get();



  try {
    alert::Alert alert = parser_.parseJson(alert_body);

    //TODO delete this in Future
    // ONLY FOR TESTING PURPOSES. TEST + KAPACITOR
    /*std::shared_ptr<Factory> factory = std::make_shared<MatrixFactory>();
    auto preparer = factory->createPreparer();
    auto prepared_alert = preparer->prepare(alert);
    auto sender = factory->createSender("!peaLsZdtyOLKogIHZJ:matrix.org");
    sender->send(prepared_alert);*/


    std::string task_id;

    //TODO uncomment this when task_id is ready
    //task_id = alert_body.at("task_id").as_string();

    auto recipient_list = ConfiguratorService().getRecipientByNotificationId(task_id);


    for(auto const& recipient: recipient_list)
    {
      std::map <std::string, std::string> chat_id_mapping;
      if(recipient.getMatrixId() != "-")
      {
        chat_id_mapping["matrix"] = recipient.getMatrixId();
        std::cerr << recipient.getMatrixId() << std::endl;
      }
      if(recipient.getTelegramChatId() != "-1")
      {
        chat_id_mapping["telegram"] = recipient.getTelegramChatId();
      }

      for(auto it = chat_id_mapping.begin(); it != chat_id_mapping.end(); ++it)
      {
        auto preparer = factories_.at(it->first)->createPreparer();
        auto prepared_alert = preparer->prepare(alert);
        auto sender = factories_.at(it->first)->createSender(it->second);
        sender->send(prepared_alert);
      }

    }

    std::cerr << "SENT!" << std::endl;
    message.reply(web::http::status_codes::OK);
  } catch (std::exception) {
    message.reply(web::http::status_codes::ServiceUnavailable);
  }
}