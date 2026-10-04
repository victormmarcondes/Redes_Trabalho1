#pragma once

#include <cstdint>
#include <vector>

class Server{
    public:
        enum class Server_Type : uint8_t{
            HTTP,
            MQTT,
            WEBSOCKETS,
        };
        virtual auto connect() -> void = 0;
        virtual auto disconnect() -> void = 0;

        virtual auto send(std::vector<uint8_t> message) -> void = 0;
        virtual auto read() -> void = 0;
};