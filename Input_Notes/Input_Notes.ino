#include "pitches.h"

const int buzzerPin = 46;  // Change if needed for Arduino

// Array storing all pitch values in order
int notes[] = {
  B0, C1, CS1, D1, DS1, E1, F1, FS1, G1, GS1, A1, AS1, B1,
  C2, CS2, D2, DS2, E2, F2, FS2, G2, GS2, A2, AS2, B2,
  C3, CS3, D3, DS3, E3, F3, FS3, G3, GS3, A3, AS3, B3,
  C4, CS4, D4, DS4, E4, F4, FS4, G4, GS4, A4, AS4, B4,
  C5, CS5, D5, DS5, E5, F5, FS5, G5, GS5, A5, AS5, B5,
  C6, CS6, D6, DS6, E6, F6, FS6, G6, GS6, A6, AS6, B6,
  C7, CS7, D7, DS7, E7, F7, FS7, G7, GS7, A7, AS7, B7,
  C8, CS8, D8, DS8
};

const int numNotes = sizeof(notes) / sizeof(notes[0]);

void setup() {
    Serial.begin(9600);
    pinMode(buzzerPin, OUTPUT);
    Serial.println("Enter a number (5-88) to play a pitch:");
}

void loop() {
    readSerialAndPlayTone();
}

void readSerialAndPlayTone() {
    if (Serial.available() > 0) {
        int inputNum = Serial.parseInt();  // Read input as an integer

        if (inputNum >= 1 && inputNum <= numNotes) {
            int noteIndex = inputNum - 1;  // Adjust for array index
            int frequency = notes[noteIndex];

            Serial.print("Playing note ");
            Serial.print(inputNum);
            Serial.print(" at ");
            Serial.print(frequency);
            Serial.println(" Hz");

            tone(buzzerPin, frequency, 300);
            delay(350);  // Small delay before next input
        } else {
            Serial.println("");
        }
    }
}
