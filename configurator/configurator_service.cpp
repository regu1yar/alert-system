#include <cpprest/http_client.h>
#include <cpprest/uri.h>
#include <cpprest/json.h>

#include "configurator_service.hpp"


std::vector<Recipient> ConfiguratorService::getRecipientByNotificationId(const std::string & notification_id) {
  auto request_string = web::uri_builder(U("/api"))
          .append_path("notifications")
          .append_query("kapacitor_task_id", notification_id)
          .to_string();

  auto recipients_request = pplx::create_task([=](){ return makeRequest(request_string); })
          .then([=](web::http::http_response response){
            if (response.status_code() != 200) {
              throw std::runtime_error(
                "Returned " + std::to_string(response.status_code()) +
                "\nResponse is" + response.extract_string().get());
            }

            std::vector<Recipient> recipients;

            auto json_body = response.extract_json();
            json_body.wait();
            for (auto recipient_object : json_body.get().as_array()) {
              recipients.emplace_back(Recipient(recipient_object.at("user")));
            }
            return recipients;
          });

  try {
    auto status = recipients_request.wait();
    return recipients_request.get();
  } catch (const std::exception& e) {
    std::cout << e.what() ;
  }
}

pplx::task<web::http::http_response> ConfiguratorService::makeRequest(const std::string & request_string) {
  return web::http::client::http_client(U(CONFIGURATOR_HOST)).request(web::http::methods::GET, request_string);
}
