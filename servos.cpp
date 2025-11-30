#include <Arduino.h>
#include "servos.h"
#include <WebServer.h>

Servo servo1;
Servo servo2;
int servo1Pos = 0;
int servo2Pos = 0;

extern WebServer server;

void initServos() {
  servo1.setPeriodHertz(50);
  servo1.attach(servo1Pin, 500, 2400); 

  servo2.setPeriodHertz(50);
  servo2.attach(servo2Pin, 500, 2600); 

  servo1.write(0);
  servo2.write(0);
}

void handleServo() {
  int id = server.arg("id").toInt();
  if (server.hasArg("pos")) {
    int pos = constrain(server.arg("pos").toInt(), 0, 180);
    if (id == 1) {
      servo1Pos = pos;
      servo1.write(servo1Pos);
    } else if (id == 2) {
      servo2Pos = pos;
      servo2.write(servo2Pos);
    }
  } else {
    if (id == 1) {
      servo1Pos = (servo1Pos == 0 ? 180 : 0);
      servo1.write(servo1Pos);
    }
    if (id == 2) {
      servo2Pos = (servo2Pos == 0 ? 180 : 0);
      servo2.write(servo2Pos);
    }
  }
  server.send(200, "text/plain", "OK");
}