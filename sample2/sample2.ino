// モータ
const int pwm_r1 = 9 ; //Arduino の 2 番ピンに対応
const int pwm_r2 = 3;
const int pwm_l1 = 10;
const int pwm_l2 = 11;

// const int motor_r1 = 2;
// const int motor_r2 = 3;
// const int pwm_motor_r = 10;
// const int motor_l1 = 4;
// const int motor_l2 = 5;
// const int pwm_motor_l = 11;
const int threshold = 980;

// フォトリフレクタ
const int sensor0 = A0;
const int sensor1 = A1;

// センサから読み取った値（analog）
int val0 = 0;
int val1 = 0;

int flag = 0;

void setup() {
  pinMode(pwm_r1, OUTPUT); //motor_r1 に対応するピン（2 番）を出力ポートに設定
  pinMode(pwm_r2, OUTPUT);
  pinMode(pwm_l1, OUTPUT);
  pinMode(pwm_l2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  // センサの値をアナログ値で読み取る
  val0 = analogRead(sensor0);
  val1 = analogRead(sensor1);
  
  bool judgeA0 = val0 > threshold;
  bool judgeA1 = val1 > threshold;

  if(judgeA0){
    analogWrite(pwm_r1, 150);
    analogWrite(pwm_r2, 0);
    analogWrite(pwm_l1, 150);
    analogWrite(pwm_l2, 0);
    //delay(20);
  }else{
    analogWrite(pwm_r1, 0);
    analogWrite(pwm_r2, 150);
    analogWrite(pwm_l1, 0);
    analogWrite(pwm_l2, 150);
    //delay(20);
  }


}