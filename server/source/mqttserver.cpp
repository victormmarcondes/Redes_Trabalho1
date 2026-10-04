#include "mqttserver.h"

#include <chrono>
#include <mqtt/async_client.h>
#include <mqtt/connect_options.h>
#include <mqtt/ssl_options.h>

auto MQTT_Server::connect() -> void{
    const auto create_options = mqtt::create_options_builder()
        .server_uri(address)
        .client_id(ID)
        .finalize();
    const auto connect_options = mqtt::connect_options_builder()
        .clean_session(true)
        .clean_start(true)
        .automatic_reconnect(true)
        .finalize();
    mqtt_client = std::make_unique<mqtt::async_client>(create_options);
    mqtt_client->subscribe("message/*", 1);
    mqtt_client->start_consuming();

    read();
}

auto MQTT_Server::disconnect() -> void{
    while (!mqtt_client->get_pending_delivery_tokens().empty()){
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
    return;
}

auto MQTT_Server::read() -> void{
    while(true){
        auto message = mqtt_client->consume_message();
        if(!message) continue;

        auto topic = message->get_topic();
        auto id_substr = topic.substr(sizeof("message/"));
        auto id = std::stoi(id_substr);

        auto payload = message->get_payload();
    }
}

auto MQTT_Server::send(std::vector<uint8_t> message) -> void{

    mqtt_client->publish("server" , message.data(), message.size(), 1, false);
    return;
}