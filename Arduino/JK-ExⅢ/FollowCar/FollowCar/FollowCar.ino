// モータ
const int pwm_r1 = 9 ; //Arduino の 2 番ピンに対応
const int pwm_r2 = 3;
const int pwm_l1 = 10;
const int pwm_l2 = 11;

const int threshold = 980;
const int speed = 40;

// センサ
int TRIG = 3;
int ECHO1 = 2;
int ECHO2 = 1;

//PIDに使用する変数
int duty1, duty2;//速度
const float Target=15;
const float Kp = 10;
const float Ki = 0.15;
const float Kd = 0.1;
float P, I, D;
float pretime;


void setup() {
  pinMode(pwm_r1, OUTPUT); //motor_r1 に対応するピン（2 番）を出力ポートに設定
  pinMode(pwm_r2, OUTPUT);
  pinMode(pwm_l1, OUTPUT);
  pinMode(pwm_l2, OUTPUT);
  pinMode(ECHO1, INPUT);
  pinMode(ECHO2, INPUT);
  pinMode(TRIG, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  // センサの値をアナログ値で読み取る
  //センサーは3つの想定
  // val0 = analogRead(sensor0);
  // val1 = analogRead(sensor1);
  // val2 = analogRead(sensor2);
  
  // bool judgeA0 = val0 > threshold;
  // bool judgeA1 = val1 > threshold;
  // bool judgeA2 = val2 > threshold;
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2); 
  digitalWrite( TRIG, HIGH );
  delayMicroseconds( 10 ); 
  digitalWrite( TRIG, LOW );

  int t1 = pulseIn(ECHO1, HIGH); //右輪
  int t2 = pulseIn(ECHO2, HIGH); //左輪
  float temp = 22.4; //気温
  float v = (331.4 + 0.6*temp) / 10000; //音速cm/μs
  float distance1 = v * (t1 / 2);
  float distance2 = v * (t2 / 2);
  float dt = (micros() - pretime) / 1000000;
  pretime = micros();
  float P1, P2, preP1 = 0, preP2 = 0;

  P1 = distance1 - Target;
  duty1 = calc_duty(distance1, dt, preP1);
  preP1 = P1;

  P2 = distance2 - Target;
  duty2 = calc_duty(distance2, dt, preP2);
  preP2 = P2;


  //Targetが一つだと良くない？？
  //Targetを２つ作って、ニュートラル区間を設けても良い
  //例 Target1=15, Target2=10
  // Target1以上 加速、 Target1~Target2 等速、　Target2以下　減速
  
  //duty1,P1が右輪、duty2,P2が左輪
  if(P1 > 0 && P2 > 0){
    //P1もP2もいずれも目標値から遠ざかっている
      //前進
    analogWrite(pwm_r1, duty1/Target*speed);
    analogWrite(pwm_r2, 0*speed);
    analogWrite(pwm_l1, duty2/Target*speed);
    analogWrite(pwm_l2, 0*speed);
  }
  
  //duty1,P1が右輪、duty2,P2が左輪
  if(P1 * P2 < 0){
    //P1とP2の一方が目標値より遠く、他方は目標値より近い
      //カーブ
    analogWrite(pwm_r1, duty1/Target*speed);
    analogWrite(pwm_r2, 0*speed);
    analogWrite(pwm_l1, duty2/Target*speed);
    analogWrite(pwm_l2, 0*speed);
  }

  if(P1 < 0 && P2 < 0){
    //P1もP2もいずれも目標値よりも近い
    //後退
    analogWrite(pwm_r1, 0*speed);
    analogWrite(pwm_r2, Target/duty1*speed);
    analogWrite(pwm_l1, 0*speed);
    analogWrite(pwm_l2, Target/duty2*speed);
  }
}

int calc_duty(float distance, float dt, float pre_P){
  P = distance - Target;
  I += P*dt;
  D = (P - pre_P) / dt;
  pre_P = P;
  return abs(Kp*P + Kd*D + Ki*I);
}

  //   //右に大きく曲がる
  // analogWrite(pwm_r1, 1*speed);
  // analogWrite(pwm_r2, 0*speed);
  // analogWrite(pwm_l1, 0.85*speed);
  // analogWrite(pwm_l2, 0*speed);
  // Serial.println("S3");

  // //左に少し曲がる
  // analogWrite(pwm_r1, 1*speed);
  // analogWrite(pwm_r2, 0*speed);
  // analogWrite(pwm_l1, 0.95*speed);
  // analogWrite(pwm_l2, 0*speed);
  // Serial.println("S2");

