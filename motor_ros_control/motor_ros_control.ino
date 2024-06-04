//#include <std_msgs/Empty.h>
//#include <geometry_msgs/Point32.h>/
#include <ros.h>
#include <std_msgs/Float32.h>
//encoder messages
#include <encoder.h>

// Set the pin out for the Right PWM and Left PWM
// "Right" and "Left" are relative to the motor direction and 
// doesn't make sense from a programming point of view sense 
// depending on how you wire or physcally mount the motor the direction is different.
// But when you send a signal on RPWM the motor will go one way and when you 
// send a signal on LPWM, the motor will go the other way.
int RPWM1 = 7;  // Digital/PWM pin 5 to the RPWM on the BTS7960
int LPWM1 = 6;  // Digital/PWM pin 6 to the LPWM on the BTS7960
// Enable "Left" and "Right" movement for the first wheel

int RPWM2 = 5;  // Digital/PWM pin 5 to the RPWM on the BTS7960
int LPWM2 = 4;  // Digital/PWM pin 6 to the LPWM on the BTS7960
// Enable "Left" and "Right" movement for the second wheel

int RPWM3 = 3;  // Digital/PWM pin 5 to the RPWM on the BTS7960
int LPWM3 = 2;  // Digital/PWM pin 6 to the LPWM on the BTS7960
// Enable "Left" and "Right" movement for the third wheel

ros::NodeHandle nh;

void pwm_val( const robot_tf_pkg::encoder& pwm_value){
  int pwm = 0;
  int x = pwm_value.enc1;
  int y = pwm_value.enc2;
  int z = pwm_value.enc3;

  motor(x,y,z);
}

ros::Subscriber<robot_tf_pkg::encoder> pwm("motor_value", &pwm_val );

void setup()
{
  // put your setup code here, to run once:

  // initialize all our pins to output
  for (int i = 4; i < 99; i++) {
    pinMode(i, OUTPUT);
  }
  delay(1000);// wait a second
  Serial.begin(9600);
  stops();
  
  //enable "Right" and "Left" movement on the HBridge
  // Notice use of digitalWrite to simply turn it on and keep it on.
  nh.initNode();
  nh.subscribe(pwm);
}

void loop()
{  
  nh.spinOnce();
  delay(1);
}

void stops(){
  analogWrite(LPWM1, 0);
  analogWrite(LPWM2, 0);
  analogWrite(LPWM3, 0);
  analogWrite(RPWM1, 0);
  analogWrite(RPWM2, 0);
  analogWrite(RPWM3, 0);
}

void motor1(int x)
{
  if (x < 0){
    analogWrite(RPWM1, x);
  }
  else if (x > 0) {
    analogWrite(LPWM1, x);
  }
  else {
    analogWrite(LPWM1, 0);
    analogWrite(RPWM1, 0);
  }
}

void motor2(int y)
{
  if (y < 0){
    analogWrite(RPWM2, y);
  }
  else if (y > 0) {
    analogWrite(LPWM2, y);
  }
  else {
    analogWrite(LPWM2, y);
    analogWrite(RPWM2, y);
  }
}

void motor3(int z)
{
  if (z < 0){
    analogWrite(RPWM3, z);
  }
  else if (z > 0) {
    analogWrite(LPWM3, z);
  }
  else {
    analogWrite(LPWM3, z);
    analogWrite(RPWM3, z);
  }
}

void motor(int x, int y, int z)
{
  if (x < 0){
    analogWrite(RPWM1, abs(x));
  }
  else if (x > 0) {
    analogWrite(LPWM1, x);
  }
  else if (x == 0) {
    analogWrite(LPWM1, 0);
    analogWrite(RPWM1, 0);
  }
  
  else if (y < 0){
    analogWrite(RPWM2, abs(y));
  }
  else if (y > 0) {
    analogWrite(LPWM2, y);
  }
  else if (y == 0) {
    analogWrite(LPWM2, 0);
    analogWrite(RPWM2, 0);
  }

    else if (z < 0){
    analogWrite(RPWM3, abs(z));
  }
  else if (z > 0) {
    analogWrite(LPWM3, z);
  }
  else if (z == 0) {
    analogWrite(LPWM3, 0);
    analogWrite(RPWM3, 0);
  }
}
