#include <Servo.h> //include servo.h library
Servo myservo;
int pos = 0;
boolean fire = false;
unsigned long thoigian;
int khoangcach;
#define trig 13
#define echo 12
#define Left 9
#define Right 10
#define Forward 8
#define buz 6
#define RM1 4
#define RM2 5
#define LM1 3
#define LM2 2
#define pump 7
void setup()
{
Serial.begin(9600);
pinMode(Left, INPUT);
pinMode(Right, INPUT);
pinMode(Forward, INPUT);

pinMode(LM1, OUTPUT);
pinMode(LM2, OUTPUT);
pinMode(RM1, OUTPUT);
pinMode(RM2, OUTPUT);
pinMode(pump, OUTPUT);
pinMode(trig, OUTPUT);
pinMode(echo, INPUT);
pinMode(buz,OUTPUT);
myservo.attach(11);
myservo.write(90);
}
void Stop()
{
digitalWrite(LM1, HIGH);
digitalWrite(LM2, HIGH);
digitalWrite(RM1, HIGH);
digitalWrite(RM2, HIGH);
}
void GoForward()
{
digitalWrite(LM1, HIGH);
digitalWrite(LM2, LOW);
digitalWrite(RM1, HIGH);
digitalWrite(RM2, LOW);
}
void GoRight()
{
digitalWrite(LM1, HIGH);
digitalWrite(LM2, LOW);
digitalWrite(RM1, HIGH);
digitalWrite(RM2, HIGH);
}
void GoLeft()
{
digitalWrite(LM1, HIGH);
digitalWrite(LM2, HIGH);
digitalWrite(RM1, HIGH);
digitalWrite(RM2, LOW);
}
int Distance()
{
int distance;
digitalWrite(trig,0); //Tắt chân trig
delayMicroseconds(2);
digitalWrite(trig,1); //bật chân trig để phát xung

delayMicroseconds(10); //Xung có độ rộng là 10 microsecond
digitalWrite(trig,0);
//Chân echo sẽ nhận xung phản xạ lại
//Và đo độ rộng xung cao ở chân echo
thoigian = pulseIn (echo, HIGH);
distance = int (thoigian / 2 / 29.412);
return distance;
}
void put_off_fire()
{
delay (500);
digitalWrite(pump, HIGH);
delay(500);
for (pos = 50; pos <= 130; pos += 1) {
myservo.write(pos);
delay(10);
}
for (pos = 130; pos >= 50; pos -= 1) {
myservo.write(pos);
delay(10);
}
digitalWrite(pump,LOW);
myservo.write(90);
fire=false;
}
void loop()
{
myservo.write(90); //Sweep_Servo();
if (digitalRead(Left) ==1 && digitalRead(Right)==1 &&
digitalRead(Forward) ==1)
{
digitalWrite(buz,LOW);
Stop();
}
else if (digitalRead(Forward) ==0)
{
GoForward();
digitalWrite(buz,HIGH);

fire = true;
}
else if (digitalRead(Left) ==0)
{
GoLeft();
digitalWrite(buz,HIGH);
}
else if (digitalRead(Right) ==0)
{
GoRight();
digitalWrite(buz,HIGH);
}
khoangcach = Distance();
if (fire ==true){
if (khoangcach>=25){
GoForward();
}
else {
Stop();
put_off_fire();
}
}
}