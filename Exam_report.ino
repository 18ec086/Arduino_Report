int speedPin = 3; 
int motor1APin = 6; 
int motor2APin = 7; 
int ledPin = 13; 
int speed_value_motor1; 

int serial_pin=12;
int old=0;
int val=0;
int state=0;

byte interruptState = 0;
void setup() {
 pinMode(speedPin, OUTPUT);
 pinMode(motor1APin, OUTPUT); 
 pinMode(motor2APin, OUTPUT); 
 pinMode(ledPin, OUTPUT);
 pinMode(serial_pin, INPUT);
}
 
void loop() {
  sw_OnOff();
  question();
}
//スイッチが押された、離された場合のふるまいを記述
void sw_OnOff(){
  val=digitalRead(serial_pin);
  if(val==HIGH&&old==LOW){
    state=!state;
    delay(10);//チャタリング防止
  }
  if(val==HIGH&&old==HIGH){
    delay(10);//チャタリング防止
  }
  old=val;
}
void question(){
  //問題の内容
  if(state==1){
    for(int i=0;i<5;i++){
      quick_motor();
    }
    while(1){
      slow_motor();
      if(digitalRead(serial_pin)){
        state=0;
        break;
      }
    }
  }
  else{
    sw_off();
  }
}
//モータをspeed_value(0~255)でPWM制御
void motor(int speed_value){
 digitalWrite(motor1APin, LOW); 
 digitalWrite(motor2APin, HIGH); 
 analogWrite(speedPin,speed_value);
}
//停止状態
void sw_off(){
  motor(0);
  led(ledPin,5000);
}
//低速状態
void slow_motor(){
  motor(127);
  led(ledPin,2000);
}
//高速状態
void quick_motor(){
  motor(250);
  led(ledPin,500);
  
}
//pin番号のLEDをperiod_timeごとにON,OFF
void led(int pin,int period_time){
    digitalWrite(pin, HIGH);
    delay(period_time);
    digitalWrite(pin, LOW);
    delay(period_time);
}
