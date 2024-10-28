
const int switchPin = 2;     // Pin connected to the aluminum foil switch
const int ledPin = 13;       // Pin connected to breadboard led

// Setup function runs once when the program starts
void setup() {
  pinMode(switchPin, INPUT);   // Set the switch pin as an input
  pinMode(ledPin, OUTPUT);     // Set the LED pin as an output
}

// Main loop function runs repeatedly
void loop() {
  int switchState = digitalRead(switchPin);   // Read the state of the switch (HIGH or LOW)
  
  if (switchState ==HIGH) {      // If the switch is OPEN - the foils are touching
    digitalWrite(ledPin, HIGH);   // Turn on the LED
  } else {                        // If the switch is closed - the foils are not touching)
    digitalWrite(ledPin, LOW);    // Turn off the LED
  }
}
