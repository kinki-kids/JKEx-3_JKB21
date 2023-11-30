// 追従用プログラム
// digitalWriteを用いない

// モータ
const int pwm_r1 = 9 ; //Arduino の 2 番ピンに対応
const int pwm_r2 = 3;
const int pwm_l1 = 10;
const int pwm_l2 = 11;
const int target = 10; // 車体間の距離をこの値に保つ
int TRIG = 3;
int ECHO = 2;
double duration = 0;
double distance = 0;
double speed_of_sound = 331.5 + 0.6 * 25; // 25℃の気温の想定

void setup() {
  Serial.begin(9600);
  pinMode(pwm_r1, OUTPUT); //motor_r1 に対応するピン（2 番）を出力ポートに設定
  pinMode(pwm_r2, OUTPUT);
  pinMode(pwm_l1, OUTPUT);
  pinMode(pwm_l2, OUTPUT);
  pinMode(ECHO, INPUT );
  pinMode(TRIG, OUTPUT );
}

void loop() {
//LOWのときは超音波を出さない、HIGHのときに出す
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2); 
  digitalWrite(TRIG, HIGH);
  delayMicroseconds( 10 ); 
  digitalWrite(TRIG, LOW);
  duration = pulseIn(ECHO, HIGH); // 往復にかかった時間が返却される[マイクロ秒]

  if (duration > 0) {
    duration = duration / 2; // 往路にかかった時間
    distance = duration * speed_of_sound * 100 / 1000000;
    Serial.print("Distance:");
    Serial.print(distance);
    Serial.println(" cm");
  }

  // ditsnceの値で条件分岐
  if(distance < target){
    //ターゲット値より小さければ後進
    analogWrite(pwm_r1, 0);
    analogWrite(pwm_r2, 150);
    analogWrite(pwm_l1, 0);
    analogWrite(pwm_l2, 163);
   
  }else if(distance == target){
    //同じならブレーキ
    analogWrite(pwm_r1, 0);
    analogWrite(pwm_r2, 10);
    analogWrite(pwm_l1, 0);
    analogWrite(pwm_l2, 10);
   
  }else if(distance > target){
    //ターゲット値より大きければ前進
     analogWrite(pwm_r1, 150);
     analogWrite(pwm_r2, 0);
     analogWrite(pwm_l1, 163);
     analogWrite(pwm_l2, 0);

  }

  delay(200);


}
