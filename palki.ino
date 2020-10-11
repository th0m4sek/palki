#include <Servo.h>

Servo myservo;
int i,tryb,Button1,Button2,Button3 = 0;
unsigned long time,sceneStart =0;

unsigned long scene1[] = {500,      //cztery krotkie
                         1000,
                         1500,
                         2000,};

unsigned long scene2[] = {2000,     //program wlsciwy
                          2500,
                          4000,
                          6000,
                          6600,
                          8000,
                         10000,
                         12000,
                         15000,
                         17000,
                         19000,
                         22000,
                         24000,
                         28000};

int scene1size = (sizeof(scene1) / sizeof(scene1[0]));
int scene2size = (sizeof(scene2) / sizeof(scene2[0]));

void(* resetFunc) (void) = 0;

void ruchServa() {
  myservo.write(180);                           // ustaw serwo
  delay(250);                                   // poczekaj az dojedzie
  }

void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  myservo.attach(9);
}

void loop() {
  time = millis();
  myservo.write(90);                            // powrot serva
  Button1 = !digitalRead(2);                    // sprawdzanie przyciskow
  Button2 = !digitalRead(3);
  Button3 = !digitalRead(4);
  
  if (Button1) {                                // 4 szybkie kliki
    tryb = 1;
    i = 0;
    sceneStart = time;
  }
  
  if (Button2) {                                // klikanie w czasie
    tryb = 2;
    i = 0;
    sceneStart = time;
  }  
  
  if (Button3) {                                // jeden klik jeden ruch serwa
    tryb = 0;
    ruchServa();
  }

  switch (tryb) {

    case 1 :                                    // tryb pierwszy                        
      if (scene1[i] <= time-sceneStart) {       // jesli czas aktywacji jest wiekszy rowny niz ten w "grafiku"
        ruchServa();
        i = i + 1;                              // nastepny krok
        if ( i == scene1size ) { resetFunc(); } // resetuj mikrokontrolej jesli dojechales do konca tablicy
      }                                         // resetowanie kasuje czas i przywraca wszystkie zmienne
      break;

    case 2 :
      if (scene2[i] <= time-sceneStart) {
        ruchServa();
        i = i + 1;
        if ( i == scene2size ) { resetFunc(); }
      }
      break;
  }
}
