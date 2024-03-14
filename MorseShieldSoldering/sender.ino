#define LATCH_PIN 10
#define CLOCK_PIN 12
#define DATA_PIN 11
#define PM_PIN A0

#define SENDER 9

int timeout = 0;
String receivedMessage = "";
String resultMessage = "";
String inputString = "";

const char letters[] = {
  'A',
  'B',
  'C',
  'D',
  'E',
  'F',
  'G',
  'H',
  'I',
  'J',
  'K',
  'L',
  'M',
  'N',
  'O',
  'P',
  'Q',
  'R',
  'S',
  'T',
  'U',
  'V',
  'W',
  'X',
  'Y',
  'Z',
  '0',
  '1',
  '2',
  '3',
  '4',
  '5',
  '6',
  '7',
  '8',
  '9',
  ' '
};

String morse_symbols[] = {
  ".-",
  "-...",
  "-.-.",
  "-..",
  ".",
  "..-.",
  "--.",
  "....",
  "..",
  ".---",
  "-.-",
  ".-..",
  "--",
  "-.",
  "---",
  ".--.",
  "--.-",
  ".-.",
  "...",
  "-",
  "..-",
  "...-",
  ".--",
  "-..-",
  "-.--",
  "--..",
  "-----",
  ".----",
  "..---",
  "...--",
  "....-",
  ".....",
  "-....",
  "--...",
  "---..",
  "----."
};

void setup() {
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(PM_PIN, INPUT);
  pinMode(SENDER, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  timeout = analogRead(PM_PIN);
  transmitMorse("SOS");
}

void transmitWord(String sequence) {
  for (int i = 0; i < sequence.length(); i++) {
    if (sequence[i] == '.') {
      transmitSignal(1);
    } else if (sequence[i] == '-') {
      transmitSignal(3);
    } else if (sequence[i] == ' ') {
      delay(5 * timeout);
    } else {
      delay(2 * timeout);
    }
  }
}

void transmitSignal(int duration) {
  digitalWrite(SENDER, LOW);
  delay(duration * timeout);
  digitalWrite(SENDER, HIGH);
  delay(timeout);
}

void transmitMorse(String inputString) {
  String prepared = inputString;
  Serial.println(prepared);
  for (int i = 0; i < prepared.length(); i++) {
    char currentLetter = prepared.charAt(i);
    if (currentLetter == ' ') {
      delay(7 * timeout);
    } else {
      int letterIndex = 0;
      for (int j = 0; j < 36; j++) {
        if (letters[j] == currentLetter) {
          letterIndex = j;
          break;
        }
      }
      transmitWord(morse_symbols[letterIndex]);
      Serial.print("Transmitting: ");
      Serial.println(morse_symbols[letterIndex]);
      delay(3 * timeout);
    }
  }
  delay(8 * timeout);
}
