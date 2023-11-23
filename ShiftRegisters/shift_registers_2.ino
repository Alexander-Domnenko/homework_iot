int latchPin = 5;
int clockPin = 3;
int dataPin = 7;
byte digits[10] = {
  0b11011101, // 0
  0b01010000, // 1
  0b11001110, // 2
  0b11011010, // 3
  0b01010011, // 4
  0b10011011, // 5
  0b10111111, // 6
  0b11010000, // 7
  0b11011111, // 8
  0b11111011  // 9
};
String inputString = "";

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  if (Serial.available()) {
    char userInput = Serial.read();

    inputString = inputString + userInput;
  }
  if (inputString.length() == 4) {

    int timeValue = inputString.toInt();

    int positions[] = { timeValue / 1000, (timeValue / 100) % 10, (timeValue / 10) % 10, timeValue % 10 };

    for (int u = positions[0]; u < 10; u++) {
      positions[0] = 0;
      for (int t = positions[1]; t < 10; t++) {
        positions[1] = 0;
        for (int h = positions[2]; h < 6; h++) {
          positions[2] = 0;
          for (int th = positions[3]; th < 10; th++) {
     
            digitalWrite(latchPin, LOW);
            shiftOut(dataPin, clockPin, LSBFIRST, digits[th]);
            shiftOut(dataPin, clockPin, LSBFIRST, digits[h]);
            shiftOut(dataPin, clockPin, LSBFIRST, digits[t]);
            shiftOut(dataPin, clockPin, LSBFIRST, digits[u]);
            digitalWrite(latchPin, HIGH);

            positions[3] = 0;

            delay(900);
          }
        }
      }

      inputString = "0000";
    }
  }
}

