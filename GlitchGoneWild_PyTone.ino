#include "pitches.h"

#define musicPin 3

String inputString = "";
boolean stringComplete = false;
const int led = 13;

int timerSong[] = {NOTE_C5, NOTE_C6, NOTE_GS2,
                   NOTE_C5, NOTE_C6, NOTE_GS2,
                   NOTE_C5, NOTE_C6, NOTE_GS2,
                   NOTE_C5, NOTE_C6, NOTE_GS2,
                   NOTE_C5, NOTE_C6, NOTE_GS2,
                   NOTE_C5, NOTE_C6, NOTE_GS2,
                   NOTE_C5, NOTE_C6, NOTE_GS2,
                   NOTE_C5, NOTE_C6, NOTE_GS2,
                  };

int winSong[] = {200, 400, 800, 1600, 3200};
int loseSong[] = {400, 100};
boolean done = false;

void setup() {
  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
}

void loop() {
  serialEvent(); //call the function
  // print the string when a newline arrives:
  if (stringComplete) {
    inputString.trim();
    inputString = "";
    stringComplete = false;
    Serial.println("OK");
  }

  int n = inputString.toInt();
  playTone(n);



}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}

void playTone(int a) {
  int size;
  switch (a) {
    case 1:
      size = sizeof(timerSong) / sizeof(int);

      for (int i = 0; i < size; i++) {
        tone(3, timerSong[i], 30);
        delay(300);
      };
      break;

    case 2:
      size = sizeof(winSong) / sizeof(int);

      for (int i = 0; i < size; i++) {
        tone(3, winSong[i], 400 / i);
        delay(100);
      };
      delay(100);
      for (int i = 0; i < size; i++) {
        tone(3, winSong[i], 70);
        delay(100);
      };
      break;

    case 3:
     size = sizeof(loseSong) / sizeof(int);

      for (int i = 0; i < size; i++) {
        tone(3, loseSong[i], 1000 * i);
        delay(1000);
      };

      break;

    case 4:

      break;

    default:
      break;

  };

}


