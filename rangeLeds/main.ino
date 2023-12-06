// publisher

const int trig_pin = 5;  // transmitter D1
const int echo_pin = 4;  // receiver D2

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "OPPO A5s";
const char* password = "1234567890a";

const char* mqtt_server = "broker.emqx.io";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(9600);
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }

  Serial.print("Connected to WiFi: ");
  Serial.println(WiFi.SSID());

  client.setServer(mqtt_server, mqtt_port);
  
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    if (client.connect("ESP8266_me")) {
      Serial.println("Connected to MQTT");
    } else {
      Serial.print("Failed with state ");
      Serial.println(client.state());
      delay(2000);
    }
  }
}

void loop() {
  // Trigger the ultrasonic: set 10us of HIGH on trig_pin
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);

  // Wait for the ultrasonic pulse to return
  unsigned long duration = pulseIn(echo_pin, HIGH);
  float distance_cm = duration * 0.0343 / 2.0;


  
  if (client.publish("esp/test1", String(distance_cm).c_str())) { 
    Serial.println("Message successfully sent");
  } else {
   
    Serial.println("Failed to send message");
  }

  // Allow the MQTT client to process incoming messages
  client.loop();
  
  delay(2000);
}
