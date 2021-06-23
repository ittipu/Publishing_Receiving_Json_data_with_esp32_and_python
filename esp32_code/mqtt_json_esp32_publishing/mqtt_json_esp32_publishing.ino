//Publishing Json data to mqtt broker



#include <ArduinoJson.h>
#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "NybSys_IoT";
const char* password = "NYBSYS@I0T";
const char* mqtt_broker = "192.168.1.102";
const int mqtt_port = 1883;


WiFiClient espClient;
PubSubClient client(espClient);

StaticJsonDocument<256> doc;

void setup(){
  Serial.begin(115200);
  Serial.println();

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.println("Connecting to WiFi....");
  }
  Serial.println("Connected to the WiFi network");
  client.setServer(mqtt_broker, mqtt_port);

  while (!client.connected()){
    Serial.println("Connecting to MQTT....");

    if(client.connect("ESP32Client")){
      Serial.println("connected");
    }
    else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(200);
    }
  }
  client.subscribe("python");
}

void callback(char* topic, byte* payload, unsigned int length){
  Serial.print("Received message: ");
  Serial.print("Topic: ");
  Serial.print(topic);
  Serial.print("Paylod: ");
  String messageTemp;

  for( int i=0; i < length; i++){
    Serial.print((char)payload[i]);
    messageTemp += (char)payload[i];
  }
  Serial.println();
  
  //deserializeJson(doc, (const byte*)payload, length);
}

void loop(){
  char buffer[256];
  doc["hello"] = "world";
  doc["temp"] = "22";
  serializeJson(doc, Serial); // Json show to Serial
  Serial.println();
  Serial.println("Publishing to Broker");
  serializeJson(doc, buffer);
  client.publish("esp/test", buffer); //publish json to broker

  client.loop();
  delay(3000);
  
}
