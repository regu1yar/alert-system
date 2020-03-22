#pragma once

#include <cpprest/http_msg.h>

namespace network {

class Handler {
 public:
  virtual ~Handler() = 0;

  virtual void handleGet(web::http::http_request request) { }
  virtual void handlePost(web::http::http_request request) { }
  virtual void handlePut(web::http::http_request request) { }
  virtual void handleHead(web::http::http_request request) { }
  virtual void handleDelete(web::http::http_request request) { }
  virtual void handleConnect(web::http::http_request request) { }
  virtual void handleOptions(web::http::http_request request) { }
  virtual void handleTrace(web::http::http_request request) { }
  virtual void handlePatch(web::http::http_request request) { }
  virtual void handleMerge(web::http::http_request request) { }
};

inline Handler::~Handler() { }

} // namespace network
