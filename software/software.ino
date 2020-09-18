// Arduino code to drive a daisy-chained series of addressable haptic motors

#define datapin 8

// Send a manchester-encoded high bit
// Low for 20 microseconds, high for 280 microseconds
void sendHigh(void) {
  digitalWrite(datapin, LOW);
  delayMicroseconds(20);
  digitalWrite(datapin, HIGH);
  delayMicroseconds(120);
}

// Send a manchester-encoded low bit
// Drive pin low for 250 microseconds, high for 50 microseconds
void sendLow(void) {
  digitalWrite(datapin, LOW);
  delayMicroseconds(120);
  digitalWrite(datapin, HIGH);
  delayMicroseconds(20);
}

// Set the intensity of one motor
void setValue(int address, int value) {
  // First, send the address
  // If the haptic motor is at address n, send n manchester-encoded 1's then a zero
  for (int i=0; i<address; i++) {
    sendHigh();
  }
  sendLow();

  // Next, send the seven-bit intensity
  int bitToSend;
  for (int i=0; i<7; i++) {
    bitToSend = value & 1<<i;
    bitToSend ? sendHigh() : sendLow();
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(datapin, OUTPUT);
  digitalWrite(datapin, HIGH);
  delay(1000);
  setValue(3, 127);
  delay(1000);
  setValue(2, 127);
  delay(1000);
  setValue(1, 127);
  delay(1000);
  setValue(0, 127);
  delay(1000);
  setValue(3, 0);
  delay(1000);
  setValue(2, 0);
  delay(1000);
  setValue(1, 0);
  delay(1000);
  setValue(0, 0);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  for (signed int i=0; i<64; i++) {
    setValue(0, 2*i);
    delay(4);
    setValue(1, 127-2*i);
    delay(4);
    setValue(2, 2*i);
    delay(4);
    setValue(3, 127-2*i);
    delay(4);
  }
  for (signed int i=0; i<64; i++) {
    setValue(0, 127-2*i);
    delay(4);
    setValue(1, 2*i);
    delay(4);
    setValue(2, 127-2*i);
    delay(4);
    setValue(3, 2*i);
    delay(4);
  }
}
