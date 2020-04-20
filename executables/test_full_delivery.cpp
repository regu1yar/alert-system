//
// Created by Мхитарян Нарек on 20/04/2020.
//
#include <boost/asio/steady_timer.hpp>
#include <iostream>
#include <server/controllers/handler.h>
#include <server/controllers/router_controller.h>
#include <server/examples/router_example/runtime_utils.h>
#include <kapacitor_input/alert_handler.h>

int main(int argc, const char * argv[]) {
    InterruptHandler::hookSIGINT();

    std::string s = "http://host_auto_ip4:4200";
    s += '0';
    s += "/api/";

    network::RouterController server(s
            , {{"send/", new AlertHandler()}});

    try {
        // wait for server initialization...
        server.accept().wait();
        std::cout << "Modern C++ RouterController now listening for requests at: " << server.endpoint() << '\n';



        InterruptHandler::waitForUserInterrupt();

        server.shutdown().wait();
    }
    catch(const std::exception & e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "somehitng wrong happen! :(" << '\n';
    }
    return 0;
}