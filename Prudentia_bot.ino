#include <SPI.h>
#include <MFRC522.h>

// Define RFID pins
#define RST_PIN     8
#define SS_PIN      9
MFRC522 rfid(SS_PIN, RST_PIN);

// Define IR sensor pins
#define LEFT_IR_SENSOR 32
#define RIGHT_IR_SENSOR 33

// Define motor pins
#define right_f1 2
#define right_fPwm 3
#define left_f1 4
#define left_fPwm 5
#define right_b1 6
#define right_b2 7
#define left_b1 22
#define left_b2 23


void setup() {
  Serial.begin(115200);
  SPI.begin();
  rfid.PCD_Init();

  pinMode(LEFT_IR_SENSOR, INPUT);
  pinMode(RIGHT_IR_SENSOR, INPUT);

  pinMode(left_f1, OUTPUT);
  pinMode(left_fpwm, OUTPUT);
  pinMode(right_f1, OUTPUT);
  pinMode(right_fpwm, OUTPUT);
  pinMode(right_b1, OUTPUT);
  pinMode(right_b2, OUTPUT);
  pinMode(left_b1, OUTPUT);
  pinMode(left_b2, OUTPUT);
}

void loop() {
  if (rfid.PICC_IsNewCardPresent()) {
    if (rfid.PICC_ReadCardSerial()) {
      String tag = "";
      for (byte i = 0; i < 5; i++) {
        tag += String(rfid.uid.uidByte[i], DEC);
      }
      tag.toUpperCase();
      
      if (tag == "532091491112") {
        lineFollowerBot();
      } else if (tag == "191521382928") {
        Serial.println("Heartrate!!")
      }
    }
  }

  int leftSensor = digitalRead(LEFT_IR_SENSOR);
  int rightSensor = digitalRead(RIGHT_IR_SENSOR);

  if (leftSensor && rightSensor) {
    moveForward();
  } else if (leftSensor && !rightSensor) {
    turnRight();
  } else if (!leftSensor && rightSensor) {
    turnLeft();
  } else {
    stop();
  }
}

void lineFollowerBot() {
  int leftSensor = digitalRead(LEFT_IR_SENSOR);
  int rightSensor = digitalRead(RIGHT_IR_SENSOR);

  if (leftSensor && rightSensor) {
    moveForward();
  } else if (leftSensor && !rightSensor) {
    turnRight();
  } else if (!leftSensor && rightSensor) {
    turnLeft();
  } else {
    stop();
  }
}

void moveForward() {
  digitalWrite(right_f1, HIGH);
  analogWrite(right_fpwm,255);
  digitalWrite(left_f1, HIGH);
  analogWrite(left_fpwm,255);
  digitalWrite(right_b1, HIGH);
  digitalWrite(right_b2, LOW);
  digitalWrite(left_b1, HIGH);
  digitalWrite(left_b2, LOW);
}

void turnLeft() {
  digitalWrite(right_f1, HIGH);
  analogWrite(right_fpwm,255);
  digitalWrite(left_f1, LOW);
  analogWrite(left_fpwm,255);
  digitalWrite(right_b1, HIGH);
  digitalWrite(right_b2, LOW);
  digitalWrite(left_b1, LOW);
  digitalWrite(left_b2, HIGH);
}

void turnRight() {
  digitalWrite(right_f1, LOW);
  analogWrite(right_fpwm,255);
  digitalWrite(left_f1, HIGH);
  analogWrite(left_fpwm,255);
  digitalWrite(right_b1, LOW);
  digitalWrite(right_b2, HIGH);
  digitalWrite(left_b1, HIGH);
  digitalWrite(left_b2, LOW);
}

void stop() {
  digitalWrite(right_f1, HIGH);
  analogWrite(right_fpwm,0);
  digitalWrite(left_f1, HIGH);
  analogWrite(left_fpwm,0);
  digitalWrite(right_b1, LOW);
  digitalWrite(right_b2, LOW);
  digitalWrite(left_b1, LOW);
  digitalWrite(left_b2, LOW);
}
