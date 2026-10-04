#include "mqttserver.h"

int main(){
    auto client = new MQTT_Server();
    client->connect();
    delete client;
}