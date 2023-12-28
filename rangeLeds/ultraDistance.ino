// subscriber

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Danyaxd";
const char* password = "ojca9707";
const char* mqttServer = "broker.emqx.io";
const int mqttPort = 1883;

const int led_pin_1 = 5;
const int led_pin_2 = 4;
const int led_pin_3 = 0;
const int led_pin_4 = 2;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(9600); 
  pinMode(led_pin_1, OUTPUT);
  pinMode(led_pin_2, OUTPUT);
  pinMode(led_pin_3, OUTPUT);
  pinMode(led_pin_4, OUTPUT);

  digitalWrite(led_pin_1, LOW);
  digitalWrite(led_pin_2, LOW);
  digitalWrite(led_pin_3, LOW);
  digitalWrite(led_pin_4, LOW);

  setup_wifi();
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
}

void setup_wifi() {
  Serial.println();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("Connecting to WiFi..");
  }
  Serial.println("Connected to WiFi: ");
  Serial.println(WiFi.SSID());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);

  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }

  int distance = atoi((char*)payload);
  Serial.print(" Distance: ");
  Serial.println(distance);

  distanceLeds(distance);

  Serial.println();
  Serial.println("-----------------------");
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    if (client.connect("ESP8266Client")) {
      Serial.println(client.subscribe("esp/test1"));
      Serial.println("Connected to MQTT");
    } else {
      Serial.print("Failed with state ");
      Serial.print(client.state());
      Serial.println(" try again in 2 seconds");
      delay(2000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}

void distanceLeds(int distance) {
  Serial.println(distance);
  if (distance <= 5) {
    digitalWrite(led_pin_1, HIGH);
    digitalWrite(led_pin_2, HIGH);
    digitalWrite(led_pin_3, HIGH);
    digitalWrite(led_pin_4, HIGH);
  } else if (distance <= 10 and distance >= 5) {
    digitalWrite(led_pin_1, HIGH);
    digitalWrite(led_pin_2, HIGH);
    digitalWrite(led_pin_3, HIGH);
    digitalWrite(led_pin_4, LOW);
  } else if (distance <= 15 and distance >= 10) {
    digitalWrite(led_pin_1, HIGH);
    digitalWrite(led_pin_2, HIGH);
    digitalWrite(led_pin_3, LOW);
    digitalWrite(led_pin_4, LOW);
  } else if (distance <= 20 and distance >= 15) {
    digitalWrite(led_pin_1, HIGH);
    digitalWrite(led_pin_2, LOW);
    digitalWrite(led_pin_3, LOW);
    digitalWrite(led_pin_4, LOW);
  } else if (distance >= 20) {
    digitalWrite(led_pin_1, LOW);
    digitalWrite(led_pin_2, LOW);
    digitalWrite(led_pin_3, LOW);
    digitalWrite(led_pin_4, LOW);
  }
}
