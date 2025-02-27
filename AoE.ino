#define light1 22
#define button1 23
char light;
unsigned long time1;

void setup() {
  // put your setup code here, to run once:
  pinMode(light1, OUTPUT);
  pinMode(button1, INPUT_PULLUP);
  light = true;
  time1 = millis();

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (light) {
    digitalWrite(light1, HIGH);
  } else {
    digitalWrite(light1, LOW);
  }

  if (light && millis() - time1 >= 4000) {
    digitalWrite(light1, LOW);
    light = false;
  }

  if (digitalRead(button1) == LOW) { 
    light = false;
  }
  
  delay(100);
}
