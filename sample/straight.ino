/* 直進するプログラム */

const int motor_r1 = 2;
const int motor_r2 = 3;
const int pwm_motor_r = 10;
const int motor_l1 = 4;
const int motor_l2 = 5;
const int pwm_motor_l = 11;
const int threshold = 980;

void setup() {
  Serial.begin(2400);
  pinMode(motor_r1, OUTPUT);
  pinMode(motor_r2, OUTPUT);
  pinMode(motor_l1, OUTPUT);
  pinMode(motor_l2, OUTPUT);
  pinMode(pwm_motor_r, OUTPUT);
  pinMode(pwm_motor_l, OUTPUT);
}

void loop() {
  
  //センサ値
  int val0 = analogRead(A0);
  int val1 = analogRead(A1);
  int val2 = analogRead(A2);

  //センサ値の表示
  Serial.print(val0);
  Serial.print(",");
  Serial.print(val1);
  Serial.print(",");
  Serial.println(val2); 

  
  if(val0 < threshold && val2 < threshold){
    //左が白かつ右が白なら直進
    //左モータ正転
    digitalWrite(motor_l1, HIGH);
    digitalWrite(motor_l2, LOW);
    analogWrite(pwm_motor_l, 150);
    //右モータ正転
    digitalWrite(motor_r1, HIGH);
    digitalWrite(motor_r2, LOW);
    analogWrite(pwm_motor_r, 150);

  }else if(val0 < threshold && val2 >= threshold){
    //左が白かつ右が黒なら左へ旋回
    //左モータブレーキ
    digitalWrite(motor_l1, HIGH);
    digitalWrite(motor_l2, HIGH);
    //右モータ正転
    digitalWrite(motor_r1, HIGH);
    digitalWrite(motor_r2, LOW);
    analogWrite(pwm_motor_r, 150);

  }else if(val0 >= threshold && val2 < threshold){
    //左が黒かつ右が白なら右へ旋回
    //左モータ正転
    digitalWrite(motor_l1, HIGH);
    digitalWrite(motor_l2, LOW);
    analogWrite(pwm_motor_l, 150);
    //右モータブレーキ
    digitalWrite(motor_r1, HIGH);
    digitalWrite(motor_r2, HIGH);
    
  }else{
    //左が黒かつ右が黒なら直進
    //左モータ正転
    digitalWrite(motor_l1, HIGH);
    digitalWrite(motor_l2, LOW);
    analogWrite(pwm_motor_l, 150);
    //右モータ正転
    digitalWrite(motor_r1, HIGH);
    digitalWrite(motor_r2, LOW);
    analogWrite(pwm_motor_r, 150);


  }

  delay(20);


}
