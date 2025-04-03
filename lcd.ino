#include <LiquidCrystal.h>
#include <SoftwareSerial.h>

SoftwareSerial Serial1(8, 9); // RX = 8, TX = 9

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

String incomingText = "";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);
  lcd.begin(16, 2);
  lcd.print("X ");
}

void loop() {
  lcd.setCursor(0, 1);
  char c = Serial1.read();

  if (c == '\n') {  // End of message
    incomingText.trim();         // Remove \r and other trailing whitespace
    lcd.clear();                 // Clear previous content
    lcd.setCursor(0, 0);         
    lcd.print(incomingText);     // Print clean message
    incomingText = "";           // Prepare for next message
  } 
  else if (isPrintable(c)) {     // Optional: skip junk characters
    incomingText += c;
  }
}