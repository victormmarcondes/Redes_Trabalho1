#include "mqttclient.h"

#include <chrono>
#include <mqtt/async_client.h>
#include <mqtt/connect_options.h>
#include <mqtt/ssl_options.h>

auto MQTT_Client::connect() -> void{
    const auto create_options = mqtt::create_options_builder()
        .server_uri(address)
        .client_id(std::to_string(ID))
        .finalize();
    const auto connect_options = mqtt::connect_options_builder()
        .clean_session(true)
        .clean_start(true)
        .automatic_reconnect(true)
        .finalize();
    mqtt_client = std::make_unique<mqtt::async_client>(create_options);
}

auto MQTT_Client::disconnect() -> void{
    while (!mqtt_client->get_pending_delivery_tokens().empty()){
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    return;
}

auto MQTT_Client::read() -> void{
    return;
}

auto MQTT_Client::send(std::vector<uint8_t> message) -> void{

    mqtt_client->publish("message/" + std::to_string(ID) , message.data(), message.size(), 1, false);
    return;
}