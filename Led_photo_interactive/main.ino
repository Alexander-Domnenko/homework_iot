#define SENSOR_PIN A0
#define LED_PIN 2

char command = ' ';
bool led_state = false;
bool alarm = false;
bool streaming = false;
bool send_one_value = false;
unsigned long previous_send_time = 0;
unsigned long previous_alarm_time = 0;
unsigned long send_count = 0;
bool manual_led_state = false;

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  unsigned long current_time = millis();
  
  process_commands();
  
  if (streaming && current_time / 100 != send_count) {
    send_photo_data();
    previous_send_time = current_time;
    send_count = current_time / 100;
    Serial.print("Time in millis:");
    Serial.println(millis());
  }
  if (send_one_value) {
    send_photo_data();
    send_one_value = false;
  }
  
  if (alarm) {
    led_alarm();
  } else {
    auto_off_on();
  }
}

void send_photo_data() {
  int val = analogRead(SENSOR_PIN);
  Serial.print("Sensor value:");
  Serial.println(val);  
}

void led_alarm() {
  unsigned long current_time = millis();

  if (current_time - previous_alarm_time >= 400) {
    previous_alarm_time = current_time;
  }
  
  if (current_time - previous_alarm_time >= 200) {
    digitalWrite(LED_PIN, HIGH);
  }
  
  if (current_time - previous_alarm_time < 200) {
    digitalWrite(LED_PIN, LOW);
  }
}

void auto_off_on(){
  int val = analogRead(SENSOR_PIN);
  if (val <= 550){
    if (!manual_led_state || led_state) {
      manual_led_state = false;
      digitalWrite(LED_PIN, HIGH);
      led_state = true;
    }
  }
  else{
    if (!manual_led_state || !led_state) {
      manual_led_state = false;
      digitalWrite(LED_PIN, LOW);
      led_state = false;
    }
  }
}

void process_commands() {
  if (Serial.available() > 0) {
    command = Serial.read();
    switch (command) {
      case 'p':
        streaming = true;
        break;
      case 's':
        streaming = false;
        send_one_value = true;
        break;
      case 'o':
        digitalWrite(LED_PIN, HIGH);
        led_state = true;
        manual_led_state = true;
        Serial.println(led_state);
        break;
      case 'f':
        digitalWrite(LED_PIN, LOW);
        led_state = false;
        manual_led_state = true;
        break;
      case 'a':
        alarm = !alarm;
        if (!alarm) {
          digitalWrite(LED_PIN, LOW);
        }
        break;
      default:
        streaming = false;
        break;
    }
  }
}