#define DATA_PIN 11
#define CLOCK_PIN 12
#define LATCH_PIN 10
#define PM_PIN A0

#define RECEIVE_PIN 2
int timeout = 0;
String receivedMessage = "";
String resultMessage = "";
String inputString = "";

byte symbols_bytes[] = {
0b11101110, // A
0b00111110, // B
0b10011010, // C
0b01111100, // D
0b10011110, // E
0b10001110, // F
0b10111010, // G
0b01011100, // H
0b00100000, // I
0b01111000, // J
0b10101110, // K
0b01110000, // L
0b10101100, // M
0b00101100, // N
0b00111100, // O
0b11001110, // P
0b11100110, // Q
0b00001100, // R
0b10110110, // S
0b00011110, // T
0b01111010, // U
0b11100000, // V
0b10101100, // W
0b01101110, // X
0b01110110, // Y
0b11011100, // Z
0b11111010, // 0
0b01100000, // 1
0b11011100, // 2
0b11110100, // 3
0b01100110, // 4
0b10110110, // 5
0b10111110, // 6
0b11100000, // 7
0b11111110, // 8
0b11100110, // 9
0b00000000,
};

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
pinMode(RECEIVE_PIN, INPUT);

Serial.begin(9600);
}

void loop() {
timeout = analogRead(PM_PIN);
receiveMorse();
}

void setDisplay(byte code) {
digitalWrite(LATCH_PIN, LOW);
shiftOut(DATA_PIN, CLOCK_PIN, LSBFIRST, code);
digitalWrite(LATCH_PIN, HIGH);
}

void printMessage(String message) {
for (int i = 0; i < message.length(); i++) {
int index = -1;
for (int j = 0; j < sizeof(letters); j++) {
if (letters[j] == message[i]) {
index = j;
}
}
if (index != -1) {
setDisplay(symbols_bytes[index]);
}
delay(300);
setDisplay(0b00000000);
delay(300);
}
}

bool transmited = false;

void receiveMorse() {
delay(1);
int idleCounter = 0;
while (digitalRead(RECEIVE_PIN) == HIGH) {
delay(timeout);
idleCounter++;
if (idleCounter > 10) {
transmited = true;
break;
}
}
if (transmited == true) {
printMessage(resultMessage);
resultMessage = "";
transmited = false;
}

if (idleCounter == 7) {
receivedMessage += "%";
} else if (idleCounter == 3) {
receivedMessage += " ";
} else if (idleCounter > 7) {
Serial.println(idleCounter);
resultMessage += decodeMorse(receivedMessage) + " ";
receivedMessage = "";
}

int signalDuration = 0;
while (digitalRead(RECEIVE_PIN) == LOW) {
delay(timeout);
signalDuration++;
}

if (signalDuration == 1) {
receivedMessage += '.';
} else if (signalDuration == 3) {
receivedMessage += '-';
}

Serial.println(receivedMessage);
delay(timeout);
}

String decodeMorse(String morseCode) {
String decoded = "";
String currentLetter = "";
for (int i = 0; i <= morseCode.length(); i++) {
char currentChar = i < morseCode.length() ? morseCode.charAt(i) : ' '; // Use a space for the last iteration
if (currentChar != ' ' && currentChar != '%') {
currentLetter += currentChar;
} else {
char recognizedLetter = '7';
for (int j = 0; j < 36; j++) {
if (currentLetter == morse_symbols[j]) {
recognizedLetter = letters[j];
break;
}
}
if (currentLetter.length() != 0) {
decoded += recognizedLetter;
currentLetter = "";
}

if (currentChar == '%') {
decoded += " ";
currentLetter = "";
}
}
}

return decoded;
}