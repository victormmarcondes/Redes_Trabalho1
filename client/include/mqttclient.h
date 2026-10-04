#pragma once

#include "client.h"

#include <string>
#include <vector>
#include <mqtt/async_client.h>



class MQTT_Client : public Client{
    public:
        MQTT_Client(unsigned int id) : ID(id) {}

        auto connect() -> void;
        auto disconnect() -> void;

        auto send(std::vector<uint8_t> message) -> void;
        auto read() -> void;

    private:
        const std::string address = "fodase";
        std::unique_ptr<mqtt::async_client> mqtt_client;
        const unsigned int ID;

};