// 追従用プログラム

const int motor_r1 = 2;
const int motor_r2 = 3;
const int pwm_motor_r = 10;
const int motor_l1 = 4;
const int motor_l2 = 5;
const int pwm_motor_l = 11;
const int target = 10; // 車体間の距離をこの値に保つ
int TRIG = 3;
int ECHO = 2;
double duration = 0;
double distance = 0;
double speed_of_sound = 331.5 + 0.6 * 25; // 25℃の気温の想定

void setup() {
  Serial.begin( 9600 );
  Serial.begin(2400);
  pinMode(motor_r1, OUTPUT);
  pinMode(motor_r2, OUTPUT);
  pinMode(motor_l1, OUTPUT);
  pinMode(motor_l2, OUTPUT);
  pinMode(pwm_motor_r, OUTPUT);
  pinMode(pwm_motor_l, OUTPUT);
  pinMode(ECHO, INPUT );
  pinMode(TRIG, OUTPUT );
}

void loop() {
//LOWのときは超音波を出さない、HIGHのときに出す
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2); 
  digitalWrite( TRIG, HIGH );
  delayMicroseconds( 10 ); 
  digitalWrite( TRIG, LOW );
  duration = pulseIn( ECHO, HIGH ); // 往復にかかった時間が返却される[マイクロ秒]

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
     //左モータ逆転
    digitalWrite(motor_l1, LOW);
    digitalWrite(motor_l2, HIGH);
    analogWrite(pwm_motor_l, 150);
    //右モータ逆転
    digitalWrite(motor_r1, LOW);
    digitalWrite(motor_r2, HIGH);
    analogWrite(pwm_motor_r, 150);
   
  }else if(distance == target){
    //同じならブレーキ
    digitalWrite(motor_l1, HIGH);
    digitalWrite(motor_l2, HIGH);
    digitalWrite(motor_r1, HIGH);
    digitalWrite(motor_r2, HIGH);

  }else if(distance > target){
    //ターゲット値より大きければ前進
     //左モータ正転
    digitalWrite(motor_l1, HIGH);
    digitalWrite(motor_l2, LOW);
    analogWrite(pwm_motor_l, 150);
    //右モータ正転
    digitalWrite(motor_r1, HIGH);
    digitalWrite(motor_r2, LOW);
    analogWrite(pwm_motor_r, 150);

  }

  delay(200);


}