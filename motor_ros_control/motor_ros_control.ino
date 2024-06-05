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
int RPWM1 = 6;  // Digital/PWM pin 5 to the RPWM on the BTS7960
int LPWM1 = 7;  // Digital/PWM pin 6 to the LPWM on the BTS7960
// Enable "Left" and "Right" movement for the first wheel

int RPWM2 = 4;  // Digital/PWM pin 5 to the RPWM on the BTS7960
int LPWM2 = 5;  // Digital/PWM pin 6 to the LPWM on the BTS7960
// Enable "Left" and "Right" movement for the second wheel

int RPWM3 = 10;  // Digital/PWM pin 5 to the RPWM on the BTS7960
int LPWM3 = 9;  // Digital/PWM pin 6 to the LPWM on the BTS7960
// Enable "Left" and "Right" movement for the third wheel
const int PWM_MIN = 1;
ros::NodeHandle nh;

void pwm_val( const robot_tf_pkg::encoder& pwm_value){
//  int pwm = 0;/
  int xa = pwm_value.enc1;
  int x = xa*255;
  int ya = pwm_value.enc2;
  int y = ya*255;
  int za = pwm_value.enc3;
  int z = za*255;

  motor1(x);
  motor2(y);
  motor3(z);
}

ros::Subscriber<robot_tf_pkg::encoder> pwm("motor_value", &pwm_val );

void setup()
{
  // put your setup code here, to run once:

  // initialize all our pins to output
  pinMode(RPWM1, OUTPUT);
  pinMode(LPWM1, OUTPUT);
  pinMode(RPWM2, OUTPUT);
  pinMode(LPWM2, OUTPUT);
  pinMode(RPWM3, OUTPUT);
  pinMode(LPWM3, OUTPUT);

  delay(1000); // Wait a second
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
  if (x < 0) {
    analogWrite(RPWM1, abs(x));
    analogWrite(LPWM1, 0);
  } else if (x > 0) {
    analogWrite(LPWM1, constrain(abs(x), PWM_MIN, 255));
    analogWrite(RPWM1, 0);
  } else {
    analogWrite(LPWM1, 0);
    analogWrite(RPWM1, 0);
  }
}

void motor2(int y){
  // Control motor 2
  if (y < 0) {
    analogWrite(RPWM2, abs(y));
    analogWrite(LPWM2, 0);
  } else if (y > 0) {
    analogWrite(LPWM2, constrain(abs(y), PWM_MIN, 255));
    analogWrite(RPWM2, 0);
  } else {
    analogWrite(LPWM2, 0);
    analogWrite(RPWM2, 0);
  }
}

void motor3(int z){
  // Control motor 3
  if (z < 0) {
    analogWrite(RPWM3, abs(z));
    analogWrite(LPWM3, 0);
  } else if (z > 0) {
    analogWrite(LPWM3, constrain(abs(z), PWM_MIN, 255));
    analogWrite(RPWM3, 0);
  } else {
    analogWrite(LPWM3, 0);
    analogWrite(RPWM3, 0);
  }
}
