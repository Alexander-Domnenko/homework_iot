#include <Arduino.h>

#define SPEED_1 5
#define DIR_1 4
#define SPEED_2 6
#define DIR_2 7

#define MAX_DISTANCE 27
#define MIN_DISTANCE 27


enum CarState {MOVE_FORWARD, ROTATE_LEFT, ROTATE_RIGHT};

const int trig_pin_forward = 11;
const int echo_pin_forward = 10;

const int trig_pin_left = 9;
const int echo_pin_left = 8;

float distance_cm_l;
float distance_cm;

int car_speed = 180; 

CarState state = MOVE_FORWARD;
unsigned long lastActionTime = 0;

void setup() {
  Serial.begin(9600);
  for (int i = 4; i < 8; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(trig_pin_forward, OUTPUT);
  pinMode(echo_pin_forward, INPUT);
  pinMode(trig_pin_left, OUTPUT);
  pinMode(echo_pin_left, INPUT);
}

void loop() {
  unsigned long currentTime = millis();
  if (currentTime - lastActionTime >= 285) {  
    switch (state) {
      case MOVE_FORWARD:
        sensor_front();
        sensor_left();
        move_forward(car_speed);
        if (distance_cm < MIN_DISTANCE) {
          state = (distance_cm_l < MAX_DISTANCE) ? ROTATE_RIGHT : ROTATE_LEFT;
          lastActionTime = currentTime;
        }
        break;
      case ROTATE_LEFT:
        rotate_left(car_speed);
        state = MOVE_FORWARD;
        lastActionTime = currentTime;
        break;
      case ROTATE_RIGHT:
        rotate_right(car_speed);
        state = MOVE_FORWARD;
        lastActionTime = currentTime;
        break;
    }
  }
}

void move_forward(int car_speed) {
  digitalWrite(DIR_1, LOW);
  digitalWrite(DIR_2, HIGH);
  analogWrite(SPEED_1, car_speed);
  analogWrite(SPEED_2, car_speed);
}

void rotate_left(int car_speed) {
  digitalWrite(DIR_1, LOW);
  digitalWrite(DIR_2, LOW);
  analogWrite(SPEED_1, car_speed);
  analogWrite(SPEED_2, car_speed);
}

void rotate_right(int car_speed) {
  digitalWrite(DIR_1, HIGH);
  digitalWrite(DIR_2, HIGH);
  analogWrite(SPEED_1, car_speed);
  analogWrite(SPEED_2, car_speed);
}

void sensor_front() {
  digitalWrite(trig_pin_forward, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin_forward, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin_forward, LOW);

  unsigned long duration = pulseIn(echo_pin_forward, HIGH);
  distance_cm = duration * 0.0343 / 2.0;
  Serial.println("distance front:" + String(distance_cm));
}

void sensor_left() {
  digitalWrite(trig_pin_left, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin_left, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin_left, LOW);

  unsigned long duration = pulseIn(echo_pin_left, HIGH);
  distance_cm_l = duration * 0.0343 / 2.0;

  Serial.println("distance le: " + String(distance_cm_l));
}
