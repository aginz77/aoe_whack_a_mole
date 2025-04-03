#include <math.h>
#include <stdio.h>

#define LIGHT1 22
#define BUTTON1 23

int numButtons = 3;

int buttons[3];
int leds[3];
unsigned long times[3];
unsigned long pressDelay[3];

unsigned long scoreDelay = 1000;

unsigned long previousButtonAssignment;
unsigned long buttonDelay = 4000;
unsigned long startingTime;

int score = 0;

void setup() {
  // put your setup code here, to run once:
  startingTime = millis();

  for (int i = 0; i < numButtons; i++) {

    pinMode(22 + 2 * i, OUTPUT); // initialize LED pins
    pinMode(23 + 2 * i, INPUT_PULLUP); // initialize button pins

    buttons[i] = 1; // initialize buttons to 1 (unpressed)
  }

  Serial.begin(9600);
  Serial1.begin(9600);

  /*Serial.println("STARTING: ");
  Serial.println("+-----------------+");
  for (int i = 0; i < numButtons; i++) {
    Serial.print("BUTTON i = " + i);
    Serial.println(digitalRead(23 + 2 * i));
  }
  for (int i = 0; i < numButtons; i++) {
    Serial.print("LED i = " + i);
    Serial.println(leds[i]);
  }
  Serial.println("+-----------------+");*/
}

void loop() {
  unsigned long t = millis(); // current time

  // put your main code here, to run repeatedly:
  for (int i = 0; i < numButtons; i++) {
    if (leds[i] == 1 && times[i] != 0 && t - times[i] >= buttonDelay) { // if light expired
      times[i] = 0; // Reset LED's time 
      leds[i] = 0; // turn off LED
    }

    digitalWrite(22 + 2 * i, leds[i]); // update LEDs

    buttons[i] = digitalRead(23 + 2 * i); // update buttons array

    if (buttons[i] == 0) { // if button[i] pressed
      Serial.print(pressDelay[i]);
      Serial.print(" ");
      Serial.println(millis());
      if (millis() - pressDelay[i] >= scoreDelay) {
        if (leds[i] == 1) {
          leds[i] = 0;                        // turn off leds[i]
          score++;
          pressDelay[i] = millis();
        } else {
          score--;
          pressDelay[i] = millis();
        }
      }
    }
  }
  
  if (t - previousButtonAssignment >= buttonDelay) { // if delay has passed light up on a new button
    previousButtonAssignment = t;
    int n = random(0, numButtons); // pick random led
    while (leds[n] == 1) {        // if already lit
      n = random(0, numButtons); // pick new button
    }
    leds[n] = 1;        // light that button
    int diff = t - startingTime;

    buttonDelay = 3000 * exp(-8.47e-6 * diff) + 1000; // decrease button delay
    printStuff(t, n);
  }
}

void printStuff(unsigned long t, int n) {
  /*Serial.println("+-----------------+");
  Serial.println(t);
  Serial.println(n);
  for (int i = 0; i < numButtons; i++) {
    Serial.print("BUTTON i = " + i);
    Serial.println(digitalRead(23 + 2 * i));
  }
  for (int i = 0; i < numButtons; i++) {
    Serial.print("LED i = " + i);
    Serial.println(leds[i]);
  }
  Serial.println("+-----------------+");*/
  Serial1.print("Score: ");
  Serial1.println(score);
}
