// This program for mqqt receive message in json format
// and deserialize the message and use in program
// This program connected with python client named "


#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

const char* ssid = "NybSys_IoT";
const char* password = "NYBSYS@I0T";

const char* mqtt_server = "192.168.1.102";
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;


StaticJsonDocument<256> doc;
void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}
void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic: ");
  Serial.print(topic);
  Serial.print(". Message: ");
  String messageTemp;
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();

  deserializeJson(doc, message, length);
  int temp = doc["timestamp"];
  Serial.print("Timestamp: "); 
  Serial.println(temp);
  String date_now = doc["day"];
  Serial.print("Day: ");
  Serial.println(date_now);
  String month_now = doc["month"];
  Serial.print("Month: ");
  Serial.println(month_now);
  String year_now = doc["year"];
  Serial.print("Year: ");
  Serial.println(year_now);

}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Subscribe
      client.subscribe("esp/light");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void loop() {
  if (!client.connected()) {
    reconnect();
  }
//  char buffer [256];
//  serializeJson(doc,buffer);
//  serializeJson(doc, Serial);
//  Serial.println();


  
  client.loop();
  delay(1000);
}
