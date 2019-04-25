#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include <WiFiClient.h>



WiFiClient wifiClient;
PubSubClient client(wifiClient);


char* ssid = WLAN-NETZWERK;
char* pw = WLAN-PASSWORT;

char* mqttServer = "stec.fh-wedel.de";
uint16_t mqttPort = 1883;
char* topic = MQTT-TOPIC;

void connectToWifi();
void reconnectToMqtt();
void callback(char* topic, byte* payload, unsigned int length);

void setup() {
  connectToWifi();
  client.setServer(mqttServer,mqttPort);
  client.setCallback(callback);

}

void loop() {
  if(WiFi.status() != WL_CONNECTED){
    connectToWifi();
  }
  if(!client.connected()){
    reconnectToMqtt();
  }
   client.loop();
}


void connectToWifi(){
  WiFi.begin(ssid,pw);
  while(WiFi.status() != WL_CONNECTED)
  {
      delay(1500);
  }
}

void reconnectToMqtt(){
  while (!client.connected()) {
    // Create a random client ID
    String clientId = "Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      client.subscribe(topic);
    } else {
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length){
  Serial.println("callback");
  newMessage = handleMessage(topic,payload,length);
  Serial.println("callback zu ende");
  currentMessage = handleOutput(currentMessage,newMessage);
}
