int latchPin = 5;
int clockPin = 3;
int dataPin = 7;
bool stopDisplay;
byte digits[10] = {
  0b11011101,  // 0
  0b01010000,  // 1
  0b11001110,  // 2
  0b11011010,  // 3
  0b01010011,  // 4
  0b10011011,  // 5
  0b10111111,  // 6
  0b11010000,  // 7
  0b11011111,  // 8
  0b11111011   // 9
};

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  Serial.begin(9600);
}
void displayDigit(int digit) {
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, digits[digit]);
  digitalWrite(latchPin, HIGH);
  delay(1000);
}

void loop() {
  if (!stopDisplay) {
    for (int i = 0; i < 10; i++) {
      displayDigit(i);

      if (Serial.available() > 0) {
        char command = Serial.read();
        if (command >= '0' && command <= '9') {
          displayDigit(command - '0');
          stopDisplay = true;  
          break;
        }
      }
    }
  }
}
