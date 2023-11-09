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
}

void loop() {
  // put your main code here, to run repeatedly:

  int val0 = analogRead(A0);//A0の値(センサ1)
  int val1 = analogRead(A1);//A1の値(センサ2)
  int val2 = analogRead(A2);
  
  bool judgeA0 = val0 > threshold;
  bool judgeA1 = val1 > threshold;

  if(judgeA0){
    digitalWrite(motor_l1, HIGH);
    digitalWrite(motor_l2, LOW);
    analogWrite(pwm_motor_l, 150);
    digitalWrite(motor_r1, HIGH);
    digitalWrite(motor_r2, LOW);
    analogWrite(pwm_motor_r, 150);
    //delay(20);
  }else{
    digitalWrite(motor_l1, LOW);
    digitalWrite(motor_l2, HIGH);
    analogWrite(pwm_motor_l, 105);
    digitalWrite(motor_r1, LOW);
    digitalWrite(motor_r2, HIGH);
    analogWrite(pwm_motor_r, 105);
    //delay(20);
  }


}