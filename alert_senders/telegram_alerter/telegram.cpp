#include "telegram.hpp"

#include <iostream>

TelegramFactory::TelegramFactory() {}

std::shared_ptr<Sender> TelegramFactory::createSender() {
  return std::make_shared<TelegramSender>();
}

std::shared_ptr<Preparer> TelegramFactory::createPreparer() {
  return std::make_shared<TelegramPreparer>();
}

////////////////////////////////////////////////////////////////////////////////

std::string TelegramPreparedAlert::getText() {
  return text_;
}

std::string TelegramPreparedAlert::getChatId() {
  return chat_id_;
}

TelegramPreparedAlert::TelegramPreparedAlert(std::string chat_id,
                                             std::string text):
        chat_id_(chat_id),
        text_(text){}

////////////////////////////////////////////////////////////////////////////////



void TelegramSender::setToken(std::string token) {
  token_ = token;
}

const std::string& TelegramSender::getToken() const {
  return token_;
}


pplx::task<http_response> TelegramSender::makeRequest(
        std::shared_ptr<TelegramPreparedAlert> telegram_alert) {
  json::value request_details;
  request_details[U("chat_id")] =
          json::value::string(U(telegram_alert->getChatId()));
  request_details[U("text")] =
          json::value::string(U(telegram_alert->getText()));

  auto request_string = uri_builder(U("/bot" + token_))
          .append_path("sendMessage")
          .to_string();
  return http_client(U("https://api.telegram.org/"))
          .request(
                  methods::POST,
                  request_string,
                  request_details);

}

pplx::task<json::value> TelegramSender::getResponse(http_response response) {
  if (response.status_code() != 200) {
    throw std::runtime_error(
            "Returned " + std::to_string(response.status_code()) +
            "\nResponse is" + response.extract_string().get());
  }
  // Convert the response body to JSON object.
  return response.extract_json();
}

void TelegramSender::send(std::shared_ptr<PreparedAlert> prepared_alert) {
  auto telegram_alert = std::static_pointer_cast<TelegramPreparedAlert>(prepared_alert);
  auto send_request =
          pplx::create_task([=]()
          { return makeRequest(telegram_alert); })
          .then([=](http_response response)
          { return getResponse(response); });

  try {
    auto status = send_request.wait();
  } catch (std::exception& e) {
    std::cout << e.what() ;
  }
}

////////////////////////////////////////////////////////////////////////////////


std::shared_ptr<PreparedAlert> TelegramPreparer::prepare(Alert alert) {
  return std::make_shared<TelegramPreparedAlert>(alert.chat_id, alert.text);
}

