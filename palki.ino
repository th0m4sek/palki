
#include <Servo.h>

Servo myservo;
int i = 0;
unsigned long time;
int Button1,Button2,Button3 = 0;

unsigned long scene[] = {2000,
               2500,
               4000,
               6000,
               6600,
               8000,
               1000,
               1200,
               1500,
               1700,
               1900,
               2200,
               2400,
               2800};

void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  myservo.attach(9);
  Serial.begin(9600);
}

void(* resetFunc) (void) = 0;

void loop() {
  //Serial.print("Time: ");
  time = millis();

  Button1 = !digitalRead(2);
  Button2 = !digitalRead(3);
  Button3 = !digitalRead(4);
  if (Button1) {
    Serial.println("B1");
  }
  if (Button2) {
    Serial.println("B2");
  }  
  if (Button3) {
    Serial.println("B3");
  }
  //Serial.println(time); //prints time since program started

  if (scene[i] <= time) {
    myservo.write(45);
    i = i + 1;
    Serial.println("servo up");
    delay(100);
    Serial.println("delay");
    myservo.write(0);
    Serial.println("servo down");
    
    Serial.print("i=");
    Serial.print(i);
  }
  
  
  
  
  if (time >= 30000) {
    Serial.println("RESET");
    delay(15);
    resetFunc();
   }
}
