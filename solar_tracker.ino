#include <Servo.h>
#include <math.h>

Servo myservox;
Servo myservoz;

int pos[] = {50, 150};

int out_pins[] = {8, 9, 10, 11};

void setup() {
  Serial.begin(9600);
  myservox.attach(3);
  myservoz.attach(5);
  for (int i=0;i<4;i++)
  {
    pinMode(out_pins[i], OUTPUT);
    digitalWrite(out_pins[i], HIGH);
  }
}

void loop() {
  int val[] = {analogRead(A0), analogRead(A1), analogRead(A2), analogRead(A3)};
  int sum = 0;
  int max = -1;
  int max_i = 0;
  for (int i=0;i<4;i++) {
    for (int j=i + 1;j<4;j++) {
      sum += abs(val[i] - val[j]);
    }
    if (val[i] > max) {
      max = val[i];
      max_i = i;
    }
  }
  sum /= 4;
  delay(10); // Pls calm down you are moving too fast
  if (sum > 100) {
    switch (max_i) { // Moving direction
      case 1: // Down left
        pos[0]--;
        pos[1]++;
        break;
      case 3: // Up right
        pos[0]--;
        pos[1]--;
        break;
      case 2: // Up left
        pos[0]++;
        pos[1]--;
        break;
      case 0: // Down right
        pos[0]++;
        pos[1]++;
        break;
    }
    myservox.write(pos[0]);
    myservoz.write(pos[1]);
  }
}
