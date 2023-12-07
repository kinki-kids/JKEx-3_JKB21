#define DELTA_T 0.010// FlexiTimer2で決めた周期
#define KP 0.165  //KP、KI、KDは車体の重さとか積んでるモーターで変わるから自分で調整してね。
#define KI 0.013
#define KD 0.0007

#include <FlexiTimer2.h>

void setup() {

  /*********モーター*********/
  pinMode(PIN_IN1_R, OUTPUT);
  pinMode(PIN_IN2_R, OUTPUT);
  pinMode(PIN_IN1_L, OUTPUT);
  pinMode(PIN_IN2_L, OUTPUT);

  /*********モニタ出力設定********/
  Serial.begin(9600);// 9600bpsでシリアル通信のポートを開きます

  /*********FlexiTimer********/
  FlexiTimer2::set(10, FLASH); //タイマー割り込み入れたほうが正確になる。面倒ならFLASH()の中身をloop()の中に入れてもいいよ。詳しくは FlexiTimer2で調べてみて。
  FlexiTimer2::start();

}

void loop() {
   RUN_RIGHT(1, Power_R);
   RUN_LEFT(1, Power_L);
}



void FLASH(){

  int sensor_RIGHT = analogRead(A5) ;        //センサーから読込む//右センサ値
  int sensor_LEFT = analogRead(A7) ;         //センサーから読込む//左のセンサ値

  Pid_val_R = PID_LIGHT_R(sensor_RIGHT, 830);
  Pid_val_L = PID_LIGHT_L(sensor_LEFT, 830);

  Power_R = constrain((80 + Pid_val_R - Pid_val_L), 0 , 255);//走り出しはPWM＝80。ここを速度制御すれば安い低トルクモータでもなんとかなるかも。
  Power_L = constrain((80 + Pid_val_L - Pid_val_R), 0 , 255);
}


//Senser_Value:センサー値、Target_Value:閾値
float PID_LIGHT_L(signed short Senser_Value, signed short Target_Value){   //左車輪のPID制御

   static signed long diff_L[2];
   static float integral_L;

   float p,i,d;

   diff_L[0] = diff_L[1]; //前回の偏差の値を格納
   diff_L[1] = Senser_Value  - Target_Value; //ターゲットとの差を格納
   integral_L  += ( diff_L[1] + diff_L[0])/ 2.0 * DELTA_T ; //積分はグラフの面積なので平均値取って長方形にして値ｘ時間

   p = KP * diff_L[1] ;   //差に比例して上昇
   i = KI * integral_L ;   //積分値
   d = KD * ( diff_L[1] - diff_L[0] )/DELTA_T ; //秒数がmsなので"偏差の差"を繰り返すだけで十分きれいな"偏差の微分"になる

   return math_limit(p+i+d);


}


float PID_LIGHT_R(signed short Senser_Value, signed short Target_Value){   //右車輪のPID制御(右車輪とアルゴリズムは一緒)

   static signed long diff_R[2];
   static float integral_R;
   
   float p,i,d;

   diff_R[0] = diff_R[1]; 
   diff_R[1] = Senser_Value  - Target_Value; 
   integral_R  += ( diff_R[1] + diff_R[0])/ 2.0 * DELTA_T ; 

   p = KP * diff_R[1] ;
   i = KI * integral_R ;
   d = KD * ( diff_R[1] - diff_R[0] )/DELTA_T ; 

   return math_limit(p+i+d);


}

//////////////////PID値の制限//////////////////
float math_limit(float pid) {
  pid = constrain(pid, -255 , 255); //定義域-255 <= pid <= 255

  return pid;
}

/***右車輪***/
#define PIN_IN1_L 9 //DIGITAL_pin 9番
#define PIN_IN2_L 8 //DIGITAL_pin 8番
#define PIN_VREF_L 11 //DIGITAL_pin 11番　//※PWM用
/***左車輪***/
#define PIN_IN1_R 5 //DIGITAL_pin 5番
#define PIN_IN2_R 4 //DIGITAL_pin 4番
#define PIN_VREF_R 6 //DIGITAL_pin 6番　//※PWM用


//////////////////右側モータ//////////////////
void RUN_RIGHT(short int n , short int power) {

  switch (n) {
    case 0://後進方向
      digitalWrite(PIN_IN1_R , LOW);
      digitalWrite(PIN_IN2_R , HIGH);
      break;

    case 1://前進方向
      digitalWrite(PIN_IN1_R , HIGH);
      digitalWrite(PIN_IN2_R , LOW);
      break;

    case 2://ブレーキ
      digitalWrite(PIN_IN1_R , HIGH);
      digitalWrite(PIN_IN2_R , HIGH);
      break;

  }
  analogWrite(PIN_VREF_R , power);//出力調整
}



/////////////////左側モータ////////////////
void RUN_LEFT(short int n , short int power) {

  switch (n) {
    case 0://後進方向
      digitalWrite(PIN_IN1_L , HIGH);
      digitalWrite(PIN_IN2_L , LOW);
      break;

    case 1://前進方向
      digitalWrite(PIN_IN1_L , LOW);
      digitalWrite(PIN_IN2_L , HIGH);
      break;

    case 2://ブレーキ
      digitalWrite(PIN_IN1_L , HIGH);
      digitalWrite(PIN_IN2_L , HIGH);
      break;

  }
  analogWrite(PIN_VREF_L , power);//出力調整
}