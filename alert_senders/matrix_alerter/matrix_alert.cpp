//
// Created by Мхитарян Нарек on 24/03/2020.
//

#pragma once

#include <iostream>
#include <string>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/uri.h>
#include <cpprest/json.h>
#include "matrix_alert.h"

using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace concurrency::streams;

std::string BasicAlert::getRoomId() {
    return "!peaLsZdtyOLKogIHZJ:matrix.org";
}

std::string BasicAlert::getMessage() {
    return alert;
}

BasicAlert::BasicAlert(std::string s)
{
    alert = s;
}

MatrixAlerter::MatrixAlerter() {

    token = "null";
    text = "";
    room_num = "";
}

void MatrixAlerter::acquireToken() {
    auto postJson = pplx::create_task([]() {
        json::value jsonObject;
        jsonObject[U("type")] = json::value::string(U("m.login.password"));
        jsonObject[U("user")] = json::value::string(U("narekito"));
        jsonObject[U("password")] = json::value::string(U("Alchemist1Edward"));

        return http_client(U("https://matrix-client.matrix.org/"))
                .request(methods::POST,
                         uri_builder(U("_matrix")).append_path(U("client")).append_path(U("r0")).append_path(U("login")).to_string(),
                         jsonObject);
    })

            // Get the response.
            .then([](http_response response) {
                // Check the status code.
                if (response.status_code() != 200) {
                    throw std::runtime_error("Returned " + std::to_string(response.status_code()));
                }

                // Convert the response body to JSON object.
                return response.extract_json();
            })

                    // Parse the user details.
            .then([=](json::value jsonObject) {
                token = jsonObject[U("access_token")].as_string();
            });
    try {
        postJson.wait();
    } catch (const std::exception &e) {
        printf("Error exception:%s\n", e.what());
    }
}

void MatrixAlerter::getRoomNum(std::string room_id) {
    room_num = room_id;
}

void MatrixAlerter::reserveToken() {
    token = "MDAxOGxvY2F0aW9uIG1hdHJpeC5vcmcKMDAxM2lkZW50aWZpZXIga2V5CjAwMTBjaWQgZ2VuID0gMQowMDI3Y2lkIHVzZXJfaWQgPSBAbmFyZWtpdG86bWF0cml4Lm9yZwowMDE2Y2lkIHR5cGUgPSBhY2Nlc3MKMDAyMWNpZCBub25jZSA9IDJDWEZJZksjcHhyZThDMkwKMDAyZnNpZ25hdHVyZSD6J5BVtG6MZfTsBzENuDZ1vtRkljZWSYwJjqkwhlVFwwo";
}

bool MatrixAlerter::sendAlert(std::string message, std::string room_id) {
    if(token == "null")
        reserveToken();
    getRoomNum(room_id);
    text = message;
    auto my_token = "m.room.message?access_token=" + token;
    auto postJson = pplx::create_task([=]() {
        json::value jsonObject;
        jsonObject[U("msgtype")] = json::value::string(U("m.text"));
        jsonObject[U("body")] = json::value::string(U(text));

        return http_client(U("https://matrix-client.matrix.org/"))
                .request(methods::POST,
                         uri_builder(U("_matrix")).append_path(U("client")).append_path(U("r0")).append_path(U("rooms")).append_path(room_num).append_path("send").append_path(my_token).to_string(),
                         jsonObject);
    })

            // Get the response.
            .then([](http_response response) {
                // Check the status code.
                if (response.status_code() != 200) {
                    throw std::runtime_error("Returned " + std::to_string(response.status_code()));
                }

                // Convert the response body to JSON object.
                return response.extract_json();
            });
    try {
        postJson.wait();
    } catch (const std::exception &e) {
        printf("Error exception:%s\n", e.what());
    }
}

auto MatrixAlerter::retToken() {
    return token;
}



