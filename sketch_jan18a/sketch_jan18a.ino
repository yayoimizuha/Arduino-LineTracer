

const int pinM0_IN1 = 3;
const int pinM0_IN2 = 9;
// 右モータ
const int pinM1_IN1 = 10;
const int pinM1_IN2 = 11;

void setup() {
  // put your setup code here, to run once:
  pinMode(0, INPUT);
  pinMode(1, INPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(pinM0_IN1, OUTPUT);
  pinMode(pinM0_IN2, OUTPUT);
  pinMode(pinM1_IN1, OUTPUT);
  pinMode(pinM1_IN2, OUTPUT);
  Serial.begin(9600);
}


void Pause(long ms) {
  long  time = millis() + ms;
  while (millis() < time + ms) {
    continue;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(analogRead(1));//dout1
  Serial.println(analogRead(2));//dout3
  Serial.println(analogRead(3));//dout2
  Serial.println("\n\n\n\n\n\n");
  //Pause(200);
  if ((analogRead(1) < 500) && (analogRead(3) < 500) && (analogRead(2) < 500)) {
    Serial.println("静止");
    analogWrite(pinM0_IN1, 0);
    analogWrite(pinM0_IN2, 0);
    analogWrite(pinM1_IN1, 0);
    analogWrite(pinM1_IN2, 0);
  }
  if ((analogRead(1) > 500) && (analogRead(3) > 500) && (analogRead(2) < 500)) {
    Serial.println("前進");
    analogWrite(pinM0_IN1, 255);
    analogWrite(pinM0_IN2, 0);
    analogWrite(pinM1_IN1, 255);
    analogWrite(pinM1_IN2, 0);
  }
  if ((analogRead(1) < 500) && (analogRead(3) < 500) && (analogRead(2) > 500)) {
    Serial.println("後進");
    analogWrite(pinM0_IN1, 0);
    analogWrite(pinM0_IN2, 100);
    analogWrite(pinM1_IN1, 0);
    analogWrite(pinM1_IN2, 120);
  }
  if ((analogRead(1) < 500) && (analogRead(3) > 500) && (analogRead(2) < 500)) {

    Serial.println("左旋回");
    analogWrite(pinM0_IN1, 200);
    analogWrite(pinM0_IN2, 0);
    analogWrite(pinM1_IN1, 0);
    analogWrite(pinM1_IN2, 0);
  }
  if ((analogRead(1) > 500) && (analogRead(3) < 500) && (analogRead(2) < 500)) {
    Serial.println("右旋回");
    analogWrite(pinM0_IN1, 0);
    analogWrite(pinM0_IN2, 0);
    analogWrite(pinM1_IN1, 175);
    analogWrite(pinM1_IN2, 0);
    analogWrite(pinM1_IN1, 225);
  }
}
