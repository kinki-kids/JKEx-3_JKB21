#include <DateTime.h>
#include <DateTimeStrings.h>

const int motor_r1 = 2;
const int motor_r2 = 3;
const int pwm_motor_r = 10;
const int motor_l1 = 4;
const int motor_l2 = 5;
const int pwm_motor_l = 11;
const int threshold = 980;

void setup() {
  Serial.begin(2800);
  pinMode(motor_r1, OUTPUT);
  pinMode(motor_r2, OUTPUT);
  pinMode(motor_l1, OUTPUT);
  pinMode(motor_l2, OUTPUT);
  pinMode(pwm_motor_r, OUTPUT);
  pinMode(pwm_motor_l, OUTPUT);
  bool pre_val0 = FALSE;
  bool pre_val1 = FALSE;
  int count6 = 0;
  double start_time;
  double end_time;
  double round_time;
}

void loop() {
  // put your main code here, to run repeatedly:

  int val0 = analogRead(A0);//A0の値(センサ1)
  int val1 = analogRead(A1);//A1の値(センサ2)
  int val2 = analogRead(A2);
  String str;
  pre_val0 = val2 > threshold;
  if(pre_val0 * pre_val1 < 0){
    count6++;

    if(count6 == 1){
      start_time = DateTime.now();
    }

    if(count6 == 7){
      count6 = 0;
      end_time = DateTime.now();
      round_time = (end_time - start_time) / 1000;
      Serial.println("Rolling time:" + String(round_time)+ " s.");
    }
  }

  // Serial.println(String(val0) + "," + String(val1));

  // Serial.print(val0);
  // Serial.print(",");
  // Serial.print(val1);
  // Serial.print(",");
  // Serial.println(val2);

  digitalWrite(motor_l1, HIGH);
  digitalWrite(motor_l2, LOW);
  analogWrite(pwm_motor_l, 150);
  digitalWrite(motor_r1, HIGH);
  digitalWrite(motor_r2, LOW);
  analogWrite(pwm_motor_r, 150);
  //delay(20);


}