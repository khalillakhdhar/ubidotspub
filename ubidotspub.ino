/****************************************
 * Include Libraries
 ****************************************/
#include "UbidotsESPMQTT.h"

/****************************************
 * Define Constants
 ****************************************/
#define TOKEN "BBFF-eZ64AEpgeqwLCgQyIHTw31cTcLgR4EcuEJLEmzGnAoz7XvmkKZc6kXC" // Your Ubidots TOKEN
#define WIFINAME "" //Your SSID
#define WIFIPASS "" // Your Wifi Pass

Ubidots client(TOKEN);

/****************************************
 * Auxiliar Functions
 ****************************************/

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  if ((char)payload[0]=='1'){
    digitalWrite(16, HIGH);
  }
  else{
    digitalWrite(16, LOW);
  }
  Serial.println();
}

/****************************************
 * Main Functions
 ****************************************/

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  client.setDebug(true); // Pass a true or false bool value to activate debug messages
  client.wifiConnection(WIFINAME, WIFIPASS);
  client.begin(callback);
  pinMode(16, OUTPUT);
  client.ubidotsSubscribe("esp8266","temperature"); //Insert the dataSource and Variable's Labels
  }

void loop() {
  // put your main code here, to run repeatedly:
  if(!client.connected()){
      client.reconnect();
      client.ubidotsSubscribe("esp8266","temperature"); //Insert the dataSource and Variable's Labels
      }
     int heartbeat = analogRead(A0); // Assuming heartbeat sensor is connected to analog pin A0

  client.add("heart",heartbeat/10);
  
  client.ubidotsPublish("chambre");
    delay(6000);
  client.loop();
  
  }
