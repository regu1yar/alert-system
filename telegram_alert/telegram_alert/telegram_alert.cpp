#include "telegram_alert.h"
#include <cpprest/filestream.h>
#include <cpprest/http_client.h>
#include <cpprest/json.h>
#include <cpprest/uri.h>
#include <iostream>

using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;

void TelegramAlert::sendAlert(uint64_t chat_id, std::string text) {
  std::string bot_name = "/bot" + token_;
  auto send_request =
          pplx::create_task([=]() {
              json::value request_details;
              request_details[U("chat_id")] = json::value::number(chat_id);
              request_details[U("text")] = json::value::string(U(text));

              return http_client(U("https://api.telegram.org/"))
                      .request(
                              methods::POST,
                              uri_builder(U(bot_name)).append_path("sendMessage").to_string(),
                              request_details);
          })

                  // Get the response.
                  .then([](http_response response) {
                      // Check the status code.
                      if (response.status_code() != 200) {
                        throw std::runtime_error(
                                "Returned " + std::to_string(response.status_code()) +
                                "\nResponse is" + response.extract_string().get());
                      }
                      // Convert the response body to JSON object.
                      return response.extract_json();
                  });

  try {
    auto status = send_request.wait();
  } catch (std::exception& e) {
    std::cout << e.what() ;
  }


}