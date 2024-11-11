#include "pitches.h"

int potPin = A0;          // Pin for potentiometer
int buttonPin = 2;        // Pin for on/off button
int speakerPin = 9;       // Pin for speaker/buzzer

int radioState = 0;       // 0 = off, 1 = on
int currentChannel = -1;  // Track current channel

// Variables for button debounce
int buttonState;          // Current state of the button
int lastButtonState = LOW; // Previous state of the button
unsigned long lastDebounceTime = 0; // Last time the button state changed
unsigned long debounceDelay = 50;   // Debounce time in milliseconds

// Song 1
int melody1[] = { NOTE_GS4, NOTE_GS4, NOTE_GS4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4,
                  NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_F4, NOTE_F4,
                  NOTE_GS4, NOTE_GS4, NOTE_GS4, NOTE_G4, NOTE_F4, NOTE_F4, NOTE_F4, NOTE_F4,
                  NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4, NOTE_G4,
                  NOTE_DS5, NOTE_D5, NOTE_DS5, NOTE_C5, REST,
                  NOTE_DS5, NOTE_D5, REST,
                  NOTE_F5, NOTE_DS5, REST,
                  NOTE_DS5, NOTE_D5, NOTE_DS5, NOTE_C5, REST,
                  NOTE_DS5, NOTE_D5, REST,
                  NOTE_F5, NOTE_DS5, REST,
                  NOTE_DS5, NOTE_D5, NOTE_DS5, NOTE_C5, REST,
                  NOTE_DS5, NOTE_D5, REST,
                  NOTE_F5, NOTE_DS5, REST,
                  NOTE_AS4, NOTE_C5, NOTE_AS5, NOTE_GS5, NOTE_G5, NOTE_G5 };
int durations1[] = { 4, 4, 4, 4, 4, 4, 4, 4,
                     4, 4, 4, 4, 4, 4, 4, 4,
                     4, 4, 4, 4, 4, 4, 4, 4,
                     4, 4, 4, 4, 4,
                     4, 4, 4, 2, 4,
                     4, 2, 4,
                     4, 2, 2,
                     4, 4, 4, 2, 4,
                     4, 2, 4,
                     4, 2, 2,
                     4, 4, 4, 2, 4,
                     4, 2, 4,
                     4, 2, 2,
                     4, 4, 4, 2, 2, 1 };

// Song 2
int melody2[] = { NOTE_A4, REST, NOTE_B4, REST, NOTE_C5, REST, NOTE_A4, REST,
                  NOTE_D5, REST, NOTE_E5, REST, NOTE_D5, REST,
                  NOTE_G4, NOTE_A4, NOTE_C5, NOTE_A4, NOTE_E5, NOTE_E5, REST,
                  NOTE_D5, REST,
                  NOTE_G4, NOTE_A4, NOTE_C5, NOTE_A4, NOTE_D5, NOTE_D5, REST,
                  NOTE_C5, REST, NOTE_B4, NOTE_A4, REST,
                  NOTE_G4, NOTE_A4, NOTE_C5, NOTE_A4, NOTE_C5, NOTE_D5, REST,
                  NOTE_B4, NOTE_A4, NOTE_G4, REST, NOTE_G4, REST, NOTE_D5, REST, NOTE_C5, REST,
                  NOTE_G4, NOTE_A4, NOTE_C5, NOTE_A4, NOTE_E5, NOTE_E5, REST,
                  NOTE_D5, REST,
                  NOTE_G4, NOTE_A4, NOTE_C5, NOTE_A4, NOTE_G5, NOTE_B4, REST,
                  NOTE_C5, REST, NOTE_B4, NOTE_A4, REST,
                  NOTE_G4, NOTE_A4, NOTE_C5, NOTE_A4, NOTE_C5, NOTE_D5, REST,
                  NOTE_B4, NOTE_A4, NOTE_G4, REST, NOTE_G4, REST, NOTE_D5, REST, NOTE_C5, REST,
                  NOTE_C5, REST, NOTE_D5, REST, NOTE_G4, REST, NOTE_D5, REST, NOTE_E5, REST,
                  NOTE_G5, NOTE_F5, NOTE_E5, REST,
                  NOTE_C5, REST, NOTE_D5, REST, NOTE_G4, REST };
int durations2[] = { 8, 8, 8, 8, 8, 8, 8, 4,
                     8, 8, 8, 8, 2, 2,
                     8, 8, 8, 8, 2, 8, 8,
                     2, 8,
                     8, 8, 8, 8, 2, 8, 8,
                     4, 8, 8, 8, 8,
                     8, 8, 8, 8, 2, 8, 8,
                     2, 8, 4, 8, 8, 8, 8, 8, 1, 4,
                     8, 8, 8, 8, 2, 8, 8,
                     2, 8,
                     8, 8, 8, 8, 2, 8, 8,
                     2, 8, 8, 8, 8,
                     8, 8, 8, 8, 2, 8, 8,
                     4, 8, 3, 8, 8, 8, 8, 8, 1, 4,
                     2, 6, 2, 6, 4, 4, 2, 6, 2, 3,
                     8, 8, 8, 8,
                     2, 6, 2, 6, 2, 1 };

// Song 3
int melody3[] = { NOTE_F4, NOTE_AS5, NOTE_GS4, NOTE_CS4, REST,
                  NOTE_AS5, NOTE_AS5, NOTE_CS6, NOTE_AS5, NOTE_AS5, NOTE_GS4, NOTE_F4,
                  NOTE_GS4, NOTE_AS5, NOTE_CS6, NOTE_AS5, NOTE_AS5, NOTE_GS4, NOTE_F4, NOTE_GS4,
                  NOTE_AS5, NOTE_CS6, NOTE_AS5, NOTE_AS5, NOTE_F5,
                  NOTE_DS5, NOTE_CS5, NOTE_AS5, NOTE_AS5, NOTE_AS5,  NOTE_GS4, NOTE_F4, NOTE_GS4,
                  NOTE_AS5, NOTE_CS6, NOTE_AS5, NOTE_AS5, NOTE_GS4, NOTE_F4, NOTE_GS4,
                  NOTE_AS5, NOTE_CS6, NOTE_AS5, NOTE_AS5, NOTE_GS4, NOTE_F4, NOTE_GS4,
                  NOTE_AS5, NOTE_CS6, NOTE_AS5, NOTE_AS5, NOTE_F5,
                  NOTE_DS5, NOTE_CS5, NOTE_AS5, NOTE_AS5, NOTE_F5, NOTE_F5, NOTE_F5,
                  REST };
int durations3[] = { 8, 4, 4, 4, 2,
                     4, 4, 4, 2, 4, 4, 4,
                     4, 4, 4, 2, 4, 4, 4,
                     4, 4, 2, 4, 2,
                     8, 8, 4, 2, 4, 4, 4, 4,
                     4, 4, 2, 4, 4, 4, 4,
                     4, 4, 2, 4, 4, 4, 4,
                     4, 4, 2, 4, 2,
                     8, 8, 4, 4, 4, 2, 2,
                     1 };

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(speakerPin, OUTPUT);
}

void playMelody(int melody[], int durations[], int size) {
  for (int note = 0; note < size; note++) {
    int noteDuration = 1000 / durations[note];
    tone(speakerPin, melody[note], noteDuration);
    delay(noteDuration * 1.3);  // Slight pause between notes
    noTone(speakerPin);
    
    // Check if the channel has changed
    int potValue = analogRead(potPin);
    int newChannel = map(potValue, 0, 1023, 1, 3);
    if (newChannel != currentChannel) {
      return;  // Exit the function if the channel changes
    }
  }
}

void loop() {
  // Read the button state and apply debounce
  int reading = digitalRead(buttonPin);

  // Check if the button state has changed
  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  // Update the radio state only if the debounce delay has passed
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading == HIGH && buttonState == LOW) {
      radioState = !radioState;  // radio on/off
      currentChannel = -1;       // Reset channel to force the replay 
    }
    buttonState = reading;
  }

  lastButtonState = reading;

  if (radioState == 1) {  // Radio is on
    int potValue = analogRead(potPin);  // Read potentiometer
    int channel = map(potValue, 0, 1023, 1, 3); //  3 channels

    if (channel != currentChannel) { // Only play if channel changed
      currentChannel = channel;
      switch (currentChannel) {
        case 1:
          playMelody(melody1, durations1, sizeof(melody1) / sizeof(int));
          break;
        case 2:
          playMelody(melody2, durations2, sizeof(melody2) / sizeof(int));
          break;
        case 3:
          playMelody(melody3, durations3, sizeof(melody3) / sizeof(int));
          break;
      }
    }
  } else {
    noTone(speakerPin); // Stop sound if radio is off
  }
}

