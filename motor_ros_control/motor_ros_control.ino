#include <ros.h>
#include <std_msgs/Float32.h>
#include <motor.h>

int RPWM1 = 6;
int LPWM1 = 7;

int RPWM2 = 3;
int LPWM2 = 2;

int RPWM3 = 5;
int LPWM3 = 4;

ros::NodeHandle nh;

void pwm_val( const robot_tf_pkg::motor& pwm_value){
  int x = pwm_value.motor1;
  int xa = x*255;
  int y = pwm_value.motor2;
  int ya = y*255;
  int z = pwm_value.motor3;
  int za = z*255;

//  motor(x,y,z);/
  motor1(x);
  motor2(y);
  motor3(z);
}

ros::Subscriber<robot_tf_pkg::motor> pwm("motor_value", &pwm_val );

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

  delay(1000);
  stops();
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

void motor(int x, int y, int z){

  if (x < 0) {
    analogWrite(RPWM1, abs(x));
    analogWrite(LPWM1, 0);
  } else if (x > 0) {
    analogWrite(LPWM1, abs(x));
    analogWrite(RPWM1, 0);
  } else {
    analogWrite(LPWM1, 0);
    analogWrite(RPWM1, 0);
  }

  if (y < 0) {
    analogWrite(RPWM2, abs(y));
    analogWrite(LPWM2, 0);
  } else if (y > 0) {
    analogWrite(LPWM2, abs(y));
    analogWrite(RPWM2, 0);
  } else {
    analogWrite(LPWM2, 0);
    analogWrite(RPWM2, 0);
  }

  if (z < 0) {
    analogWrite(RPWM3, abs(z));
    analogWrite(LPWM3, 0);
  } else if (x > 0) {
    analogWrite(LPWM3, abs(z));
    analogWrite(RPWM3, 0);
  } else {
    analogWrite(LPWM3, 0);
    analogWrite(RPWM3, 0);
  }
}

void motor1(int x){
  if (x < 0) {
    analogWrite(RPWM1, abs(x));
    analogWrite(LPWM1, 0);
  } else if (x > 0) {
    analogWrite(LPWM1, abs(x));
    analogWrite(RPWM1, 0);
  } else {
    analogWrite(LPWM1, 0);
    analogWrite(RPWM1, 0);
  }
}

void motor2(int y){
  if (y < 0) {
    analogWrite(RPWM2, abs(y));
    analogWrite(LPWM2, 0);
  } else if (y > 0) {
    analogWrite(LPWM2, abs(y));
    analogWrite(RPWM2, 0);
  } else {
    analogWrite(LPWM2, 0);
    analogWrite(RPWM2, 0);
  }
}

void motor3(int z){
  if (z < 0) {
    analogWrite(RPWM3, abs(z));
    analogWrite(LPWM3, 0);
  } else if (z > 0) {
    analogWrite(LPWM3, abs(z));
    analogWrite(RPWM3, 0);
  } else {
    analogWrite(LPWM3, 0);
    analogWrite(RPWM3, 0);
  }
}
