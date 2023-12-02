const int buttonPin = 2;
const int ledPin = 9;
const int latchPin = 5;
const int clockPin = 3;
const int dataPin = 7;

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

volatile bool countOn = false;
volatile unsigned long timerPrew = 0;
volatile unsigned long timerPrew2 = 0;
volatile bool buttonPressed = false;

boolean ledOn = false;

int adjustBrightness() {
  static unsigned long lastMillis = 0;
  static int brightness = 0;
  
  if (millis() - lastMillis >= 20) {  
    lastMillis = millis();

    brightness += 1;
    if (brightness >= 255) {
      brightness = 0;
    }
  }

  return brightness;
}



void toggleLED() {
  if ((millis() - timerPrew) >= 500) {
    countOn = false;
    timerPrew = millis();
  }
  if (!countOn) {
    countOn = true;
    if (digitalRead(buttonPin) == HIGH) {
      timerPrew2 = millis();
      ledOn = !ledOn;
      digitalWrite(ledPin, ledOn);
      buttonPressed = true;
    } else {
      buttonPressed = true;
    }
  }
}


void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(buttonPin), toggleLED, CHANGE);
}

void loop() {

  if (digitalRead(buttonPin) == HIGH && digitalRead(ledPin)) {
    if ((millis() - timerPrew2) >= 2000) {

      int currentBrightness = adjustBrightness();
      analogWrite(ledPin, currentBrightness);

      unsigned long holdDuration = (millis() - timerPrew2) / 1000;
      int displayValue = ((holdDuration / 3)) % 10;

      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, LSBFIRST, digits[displayValue]);
      digitalWrite(latchPin, HIGH);
    }

    if (digitalRead(buttonPin) == LOW) {
      digitalWrite(latchPin, LOW);
      shiftOut(dataPin, clockPin, LSBFIRST, digits[0]);
      digitalWrite(latchPin, HIGH);
    }

    digitalWrite(ledPin, HIGH);
  }

  if (buttonPressed) {
    if (digitalRead(buttonPin) == HIGH) {
      Serial.println("pressed");
    }
    if (digitalRead(buttonPin) == LOW) {
      Serial.println("unpressed");
    }
    buttonPressed = false;
  }
}

