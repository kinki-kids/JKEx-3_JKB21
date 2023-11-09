// sample_code
// Arduino Uno のピン配置
// モータ
const int pwm_r1 = 9 ; //Arduino の 2 番ピンに対応
const int pwm_r2 = 3;
const int pwm_l1 = 10;
const int pwm_l2 = 11;

// フォトリフレクタ
const int sensor0 = A0;
const int sensor1 = A1;

// センサから読み取った値（analog）
int val0 = 0;
int val1 = 0;

int flag = 0;

void setup() { //実行時に 1 回だけ実行
  pinMode(pwm_r1, OUTPUT); //motor_r1 に対応するピン（2 番）を出力ポートに設定
  pinMode(pwm_r2, OUTPUT);
  pinMode(pwm_l1, OUTPUT);
  pinMode(pwm_l2, OUTPUT);
  Serial.begin(9600);
}

void loop() { //制御プログラム
  // センサの値をアナログ値で読み取る
  val0 = analogRead(sensor0);
  val1 = analogRead(sensor1);

  // シリアルポートに読み取った値を表示させる
  //Serial.println(val1);
  if(flag == 0){
    if(val0 >= 950 && val1 >= 950){
      analogWrite(pwm_r1, 150);
      analogWrite(pwm_r2, 0);
      analogWrite(pwm_l1, 163);
      analogWrite(pwm_l2, 0);
    }else if(val0 < 950 && val1 >= 950){
      analogWrite(pwm_r1, 10);
      analogWrite(pwm_r2, 0);
      analogWrite(pwm_l1, 163);
      analogWrite(pwm_l2, 0);
    }else if(val0 >= 950 && val1 < 950){
      analogWrite(pwm_r1, 155);
      analogWrite(pwm_r2, 0);
      analogWrite(pwm_l1, 10);
      analogWrite(pwm_l2, 0);
    }else if(val0 < 950 && val1 < 950){
      flag = 1;
    }
  }else{
    if(val0 >= 950 && val1 >= 950){
      analogWrite(pwm_r1, 0);
      analogWrite(pwm_r2, 150);
      analogWrite(pwm_l1, 0);
      analogWrite(pwm_l2, 163);
    }else if(val0 < 950 && val1 >= 950){
      analogWrite(pwm_r1, 0);
      analogWrite(pwm_r2, 10);
      analogWrite(pwm_l1, 0);
      analogWrite(pwm_l2, 163);
    }else if(val0 >= 950 && val1 < 950){
      analogWrite(pwm_r1, 0);
      analogWrite(pwm_r2, 155);
      analogWrite(pwm_l1, 0);
      analogWrite(pwm_l2, 10);
    }else if(val0 < 950 && val1 < 950){
      analogWrite(pwm_r1, 150);
      analogWrite(pwm_r2, 0);
      analogWrite(pwm_l1, 163);
      analogWrite(pwm_l2, 0);
    }
  }
}