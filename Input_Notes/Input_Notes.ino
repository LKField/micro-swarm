#include "pitches.h"

const int buzzerPin = 46;  // Change if needed for Arduino

void setup() {
    Serial.begin(9600);
    pinMode(buzzerPin, OUTPUT);
    Serial.println("Enter text to change buzzer tone:");
}

void loop() {
    readSerialAndPlayTone();
}

void readSerialAndPlayTone() {
    while (Serial.available()) {
        char inputChar = Serial.read();  // Read the incoming character

        // Check if the character corresponds to a valid pitch variable
        switch (inputChar) {
            case 'B':
              Serial.println("B");
              tone(buzzerPin, B4, 200); break;
            case 'C':
              Serial.println("C");
              tone(buzzerPin, C4, 200); break;
            case 'D':
                Serial.println("D");
                tone(buzzerPin, D4, 200); break;
            case 'E':
                Serial.println("E");
                tone(buzzerPin, E4, 200); break;
            case 'F':
                Serial.println("F");
                tone(buzzerPin, F4, 200); break;
            case 'G':
                Serial.println("G");
                tone(buzzerPin, G4, 200); break;
            case 'A':
                Serial.println("A");
                tone(buzzerPin, A4, 200); break;
            // Add more cases for other notes as necessary
            default:
                Serial.println("Error - invalid input: " + inputChar);
                break;
        }

        delay(250); // Small delay before next character
    }
}
