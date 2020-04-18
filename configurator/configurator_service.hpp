#pragma once

#include "recipient.hpp"

#include <cpprest/http_client.h>
#include <string>
#include <vector>


class ConfiguratorService {
public:
  std::vector<Recipient> getRecipientByNotificationId(const std::string & notification_id);
private:
  const std::string CONFIGURATOR_HOST = "http://127.0.0.1:8000/api";

  pplx::task<web::http::http_response> makeRequest(const std::string & request_string);
};
