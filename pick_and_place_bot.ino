#include <Servo.h>

Servo theclaw;
Servo mainturn;
Servo updown;
Servo forback;

int pos, i, flag, val, pos1, angle;
char cmd, cmd1;

void setup() {
  theclaw.attach(3);
  mainturn.attach(4);
  updown.attach(5);
  forback.attach(6);
  Serial.begin(9600);
}

void checkflag() {
  if (Serial.available()) {
    cmd = Serial.read();
    Serial.print("Command: ");
    Serial.println(cmd);
  }
  if (cmd == 'A') { //Flag 1 for The claw
    flag = 1;
  }
  if (cmd == 'B') { //Flag 2 for Mainturn
    flag = 2;
  }
  if (cmd == 'C') { //Flag 3 for Updown
    flag = 3;
  }
  if (cmd == 'D') { //Flag 4 for Forback
    flag = 4;
  }
  if (cmd == 'E') { //Flag 5 for Stop
    flag = 5;
  }
  Serial.print("Flag: ");
  Serial.println(flag);
}

void CCCloop(int val, int angle) {
  while (i < angle && flag == val) {
    Serial.print("Val: ");
    Serial.println(val);
    servowrite();
    delay(10);
    i++;
    Serial.print("Angle: ");
    Serial.println(i);
    checkflag();
  }
  while (i > 0 && flag == val) {
    servowrite();
    delay(10);
    i--;
    Serial.print("Angle: ");
    Serial.println(i);
    checkflag();
  }
}

void servowrite() {
  Serial.println("Servo Write");
  Serial.println(val);
  if (val == 1) {
    theclaw.write(i);
    Serial.println("Claw Write");
    pos1 = theclaw.read();
    Serial.println(pos1);
  }

  if (val == 2) {
    mainturn.write(i);
    Serial.print("Main Write");
    pos1 = mainturn.read();
    Serial.println(pos1);
  }

  if (val == 3) {
    updown.write(i);
    Serial.print("Updown Write");
    pos1 = updown.read();
    Serial.println(pos1);
  }

  if (val == 4) {
    forback.write(i);
    Serial.print("forback Write");
    pos1 = forback.read();
    Serial.println(pos1);
  }
}

void loop() {
  if (Serial.available()) {
    checkflag();
  }
  if (flag == 2) {
    Serial.println("Main Turn");
    pos = mainturn.read();
    //Serial.println(pos);
    i = pos;
    while (flag == 2) {
      val = flag;
      CCCloop(flag, 180);
    }
  }

  if (flag == 3) {
    Serial.println("Updown");
    pos = updown.read();
    //Serial.println(pos);
    i = pos;
    while (flag == 3) {
      val = flag;
      CCCloop(flag, 130);
    }
  }

  if (flag == 4) {
    Serial.println("Forback");
    pos = forback.read();
    //Serial.println(pos);
    i = pos;
    while (flag == 4) {
      val = flag;
      CCCloop(flag, 180);
    }
  }

  if (flag == 1) {
    Serial.println("The Claw");
    pos = theclaw.read();
    //Serial.println(pos);
    i = pos;
    while (flag == 1) {
      val = flag;
      CCCloop(flag, 90);
    }
  }

  if (flag == 5) {
    Serial.println("Stop");
    while (flag == 5) {
      delay(100);
      Serial.println("Stop");
      checkflag();
    }
  }
}
