#include "mqttclient.h"

int main(){
    auto client = new MQTT_Client(15);
    delete client;
}