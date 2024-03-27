#define SPEED_1      5 
#define DIR_1        4 
#define SPEED_2      6 
#define DIR_2        7 
int state = 0;
void setup() {
  for (int i = 4; i < 8; i++) {     
    pinMode(i, OUTPUT);
  }
} 
void move_forward(int car_speed) {
  digitalWrite(DIR_1, LOW);  
  digitalWrite(DIR_2, HIGH);
  analogWrite(SPEED_1, car_speed);  
  analogWrite(SPEED_2, car_speed);
}

void move_back(int car_speed) {
  digitalWrite(DIR_1, HIGH);  
  digitalWrite(DIR_2, LOW);
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

void stop(){
  analogWrite(SPEED_1, 0);  
  analogWrite(SPEED_2, 0);
}

void turn_left(int car_speed, float steepness) {
  if(steepness > 1) {
    steepness = 1;
  }
    if(steepness < 0) {
    steepness = 0;
  }
  digitalWrite(DIR_1, LOW);  
  digitalWrite(DIR_2, HIGH);
  analogWrite(SPEED_1, car_speed);  
  analogWrite(SPEED_2, car_speed * steepness);
}

void turn_right(int car_speed, float steepness) {
  if(steepness > 1) {
    steepness = 1;
  }
    if(steepness < 0) {
    steepness = 0;
  }
  digitalWrite(DIR_1, LOW);  
  digitalWrite(DIR_2, HIGH);
  analogWrite(SPEED_1, car_speed * steepness);  
  analogWrite(SPEED_2, car_speed);
  delay(500);
  
}

 
void loop() {
  for(int i = 0; i < 4; i++) {
    move_forward(255);
    delay(2000); 
    rotate_right(255);
    delay(400);
  }
  stop();
  delay(3000);
  
    for(int i = 0; i < 4; i++) {
    move_forward(255);
    delay(2000); 
    rotate_left(255);
    delay(400);
  }
  stop();
  delay(3000);
}
