#include <Sleep_n0m1.h>

// INPUT pin配置
// タクトスイッチ
const int pinSW = 2;
// センサ（左から）
const int pinS0 = 0;
const int pinS1 = 1;
const int pinS2 = 2;
const int pinS3 = 3;
// OUTPUT pin配置
// 左モータ
const int pinM0_IN1 = 3;
const int pinM0_IN2 = 9;
// 右モータ
const int pinM1_IN1 = 10;
const int pinM1_IN2 = 11;
// LED（左から）
const int pinLED0 = 12;
const int pinLED1 = 13;
// その他各種定数
const int SW_NoResTime = 100; // チャタリング防止 100[ms]
const int S0_Th = 512; // センサー閾値
const int S1_Th = 512; // センサー閾値
const int S2_Th = 512; // センサー閾値
const int S3_Th = 512; // センサー閾値

#define SPEED 120
String RESET = String("reset");
Sleep sleep;
unsigned long sleepTime = 8.64e+7;

// プロトタイプ宣言
void Motor(bool M0_IN1, bool M0_IN2, bool M1_IN1, bool M1_IN2);
void Stop();
void SuperStop();
void Left(long  ms);
void SuperLeft(long  ms);
void BackLeft(long  ms);
void Right(long  ms);
void SuperRight(long  ms);
void BackRight(long  ms);
void Back(long  ms);
void Straight(long ms);
void Software_reset();

// the setup function runs once when you press reset or power the board
void setup() {
  // put your setup code here, to run once:
  pinMode(pinSW, INPUT);
  pinMode(pinS0, INPUT);
  pinMode(pinS1, INPUT);
  pinMode(pinS2, INPUT);
  pinMode(pinS3, INPUT);
  pinMode(pinM0_IN1, OUTPUT);
  pinMode(pinM0_IN2, OUTPUT);
  pinMode(pinM1_IN1, OUTPUT);
  pinMode(pinM1_IN2, OUTPUT);
  pinMode(pinLED0, OUTPUT);
  pinMode(pinLED1, OUTPUT);
  Serial.begin(9600);            // 9600 bpsで通信する
  Serial.println("Start");       // 最初に1度だけ Start を表示
  Serial.print("micros():");
  Serial.println(micros());

}

//******************************************  Main Routine **************************************************

void loop() {
  Left(1000);
  Right(1000);
  User_reset();





















}

//******************************************  Main Routine **************************************************

void Motor(bool M0_IN1, bool M0_IN2, bool M1_IN1, bool M1_IN2) {
  analogWrite(pinM0_IN1, M0_IN1 * SPEED);
  analogWrite(pinM0_IN2, M0_IN2 * SPEED);
  digitalWrite(pinLED0, M0_IN1 || M0_IN2);

  analogWrite(pinM1_IN1, M1_IN1 * SPEED);
  analogWrite(pinM1_IN2, M1_IN2 * SPEED);
  digitalWrite(pinLED1, M1_IN1 || M1_IN2);

}

void Stop() {
  Motor(false, false, false, false);
}

void SuperStop() {

}
void Left(long  ms) {
  long  time = millis() + ms;
  Serial.print("\n\n\n\n Left in ");
  Serial.println("time:");
  Serial.print(time);
  while (millis() < time + ms) {
    Motor(true, false, false, false);
    User_reset();
  }
  Stop();
  delay(70);
}

void SuperLeft(long  ms) {
  long  time = millis() + ms;
  Serial.print("\n\n\n\n SuperLeft in ");
  Serial.println("time:");
  Serial.print(time);
  while (millis() < time + ms) {
    Motor(true, false, false, true);
    User_reset();
  }
  Stop();
  delay(70);
}

void BackLeft(long  ms) {
  long  time = millis() + ms;
  Serial.print("\n\n\n\nBackLeft in ");
  Serial.println("time:");
  Serial.print(time);
  while (millis() < time + ms) {
    Motor(false, false, false, true);
    User_reset();
  }
  Stop();
  delay(70);
}

void Right(long  ms) {
  long  time = millis() + ms;
  Serial.print("\n\n\n\n Right in ");
  Serial.println("time:");
  Serial.print(time);
  while (millis() < time + ms) {
    Motor(false, false, true, false);
    User_reset();
  }
  Stop();
  delay(70);
}

void SuperRight(long  ms) {
  long  time = millis() + ms;
  Serial.print("\n\n\n\nSuperRight in ");
  Serial.println("time:");
  Serial.print(time);
  while (millis() < time + ms) {
    Motor(false, true, true, false);
    User_reset();
  }
  Stop();
  delay(70);
}

void BackRight(long  ms) {
  long  time = millis() + ms;
  Serial.print("\n\n\n\nBackRight in ");
  Serial.println("time:");
  Serial.print(time);
  while (millis() < time + ms) {
    Motor(false, true, false, false);
    User_reset();
  }
  Stop();
  delay(70);
}

void Back(long  ms) {
  long  time = millis() + ms;
  Serial.print("\n\n\n\nBack in ");
  Serial.println("time:");
  Serial.print(time);
  while (millis() < time + ms) {
    Motor(false, true, false, true);
    User_reset();
  }
  Stop();
  delay(70);
}

void Straight(long ms) {
  long  time = millis() + ms;
  Serial.print("\n\n\n\nStraight in ");
  Serial.println("time:");
  Serial.print(time);
  while (millis() < time + ms) {
    Motor(true, false, true, false);
    User_reset();
  }
  Stop();
  delay(70);
}


void Software_reset() {
  asm volatile(" jmp 0");
}

void User_reset() {
  if (Serial.available() > 0) {
    char text = Serial.read();
    if (text == 'R') {
      Stop();
      Software_reset();
    } else if (text == 'Q') {
      Stop();
      Serial.println("\nQuit...");
      sleep.pwrDownMode();
      sleep.sleepDelay(sleepTime);
    }
  }
}
