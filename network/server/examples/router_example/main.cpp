#include <iostream>
#include <condition_variable>
#include <mutex>
#include <signal.h>

#include "handler.h"
#include "router_controller.h"

class HelloWorldHandler : public network::Handler {
 public:
  void handleGet(network::http_request message) override {
    std::cout << "Responded to world!" << std::endl;
    message.reply(web::http::status_codes::Accepted, "Hello, world!");
  }
};

static std::condition_variable _condition;
static std::mutex _mutex;

class InterruptHandler {
 public:
  static void hookSIGINT() {
    signal(SIGINT, handleUserInterrupt);
  }

  static void handleUserInterrupt(int signal){
    if (signal == SIGINT) {
      std::cout << "SIGINT trapped ..." << '\n';
      _condition.notify_one();
    }
  }

  static void waitForUserInterrupt() {
    std::unique_lock<std::mutex> lock { _mutex };
    _condition.wait(lock);
    std::cout << "user has signaled to interrup program..." << '\n';
    lock.unlock();
  }
};

int main(int argc, const char * argv[]) {
  InterruptHandler::hookSIGINT();

  network::RouterController server("http://host_auto_ip4:42000/api/"
                                  , {{"hello/world/", new HelloWorldHandler()}});

  try {
    // wait for server initialization...
    server.accept().wait();
    std::cout << "Modern C++ RouterController now listening for requests at: " << server.endpoint() << '\n';

    InterruptHandler::waitForUserInterrupt();

    server.shutdown().wait();
  }
  catch(std::exception & e) {
    std::cerr << e.what() << std::endl;
    std::cerr << "somehitng wrong happen! :(" << '\n';
  }

  return 0;
}