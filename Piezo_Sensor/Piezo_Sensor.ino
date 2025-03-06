#include "pitches.h"

const int piezoPin = A0;  // The piezo sensor pin (change if needed)
const int buzzerPin = 46;  // The buzzer pin (change if needed)

// NOTES & PITCHES
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

// Variables for vibration reading and filtering
int vibrationReading = 0;
int limitedReading = 0;

void setup() {
  Serial.begin(9600);
  pinMode(piezoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  
  Serial.println("Piezo vibration to note demo");
}

void loop() {
  // Average 10 readings for filtering noise
  int sum = 0;
  for (int i = 0; i < 10; i++) {
    sum += analogRead(piezoPin);
    delay(10);  // Short delay between samples for smoother reading
  }
  vibrationReading = sum / 10;  // Average of 10 readings

  // Limit vibration reading to a range of 0-1023
  limitedReading = map(vibrationReading, 0, 1023, 0, numNotes - 1);

  // Print the raw and limited vibration readings to the serial monitor
  Serial.print("Raw vibration reading: ");
  Serial.print(vibrationReading);
  Serial.print("  Limited reading (0-");
  Serial.print(numNotes - 1);
  Serial.print("): ");
  Serial.println(limitedReading);

  // Play the corresponding note based on vibration
  if (vibrationReading > 200) {  // Threshold to avoid too low vibrations triggering notes
    int frequency = notes[limitedReading];
    Serial.print("Playing note at frequency: ");
    Serial.println(frequency);

    tone(buzzerPin, frequency, 300);  // Play the note for 300ms
  } else {
    noTone(buzzerPin);  // Stop the sound if no significant vibration is detected
  }

  delay(100);  // Short delay before next reading
}