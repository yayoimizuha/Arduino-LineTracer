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

#define SPEED 80
String RESET = String("reset");
Sleep sleep;
unsigned long sleepTime = 8.64e+7;
int search_line_count = 0;


struct sensors {
  bool A;
  bool B;
  bool C;
  bool D;
};
struct sensors sensor_state;
#define Sensor_Threshold 300
// プロトタイプ宣言
struct sensors Sensor();
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
void System_stop();

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
#define RANDOMSEED 10
int kantanmode = 0;
int data_one = 0;
void loop() {
  randomSeed(analogRead(pinM0_IN1));
  if (kantanmode == 0) {
    while (analogRead(pinS3) > 300) {
      digitalWrite(pinLED0, LOW);
      digitalWrite(pinLED1, LOW);
      analogWrite(pinM0_IN1, 60);
      analogWrite(pinM0_IN2, 0);
      analogWrite(pinM1_IN1, 20 + random(RANDOMSEED));
      analogWrite(pinM1_IN2, 0);
    }
    kantanmode = 1;
  }
  else {
    while (analogRead(pinS1) > 300) {
      digitalWrite(pinLED0, HIGH);
      digitalWrite(pinLED1, LOW);
      analogWrite(pinM0_IN1, 20 + random(RANDOMSEED));
      analogWrite(pinM0_IN2, 0);
      analogWrite(pinM1_IN1, 60);
      analogWrite(pinM1_IN2, 0);
    }
    if (analogRead(pinS1) > 700 && analogRead(pinS0) > 700) {
      digitalWrite(pinLED0, LOW);
      digitalWrite(pinLED1, HIGH);
      analogWrite(pinM0_IN1, 0);
      analogWrite(pinM0_IN2, 60);
      analogWrite(pinM1_IN1, 0);
      analogWrite(pinM1_IN2, 30);
      Pause(70);
    } else {
      digitalWrite(pinLED1, LOW);
    }
    if (analogRead(pinS1) < 300 && analogRead(pinS0) < 300) {
      digitalWrite(pinLED1, HIGH);
      digitalWrite(pinLED0, HIGH);
      analogWrite(pinM0_IN1, 0);
      analogWrite(pinM0_IN2, 60);
      analogWrite(pinM1_IN1, 0);
      analogWrite(pinM1_IN2, 60);
      Pause(70);
    } else {
      digitalWrite(pinLED1, LOW);
      digitalWrite(pinLED0, LOW);
    }
    kantanmode = 0;
  }
}

void Pause(long ms) {
  long  time = millis() + ms;
  while (millis() < time + ms) {
    continue;
  }
}
