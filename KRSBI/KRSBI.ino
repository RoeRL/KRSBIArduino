#include <ros.h>
//#include <std_msgs/Empty.h>
#include <geometry_msgs/Point32.h>

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

void pwm_val( const geometry_msgs::Point32& pwm_value){
  int pwm = 0;
  int x = pwm_value.x*255;
  int y = pwm_value.y*255;
  int z = pwm_value.z*255;
  
  motor1(x);
  motor2(y);
  motor3(z);
  
  return x;
  
}

ros::Subscriber<geometry_msgs::Point32> pwm("video_topic", &pwm_val );

void setup()
{
  // put your setup code here, to run once:

  // initialize all our pins to output
  for (int i = 4; i < 29; i++) {
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
  int current_speed = 0;
  int stepping_speed = 20;
  if (x < 0){
    analogWrite(RPWM1, abs(x));
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
  int current_speed = 0;
  int stepping_speed = 20;
  if (y < 0){
    while (current_speed != abs(y))
    {
      if (current_speed < abs(y))
      {
        current_speed = min(current_speed + speed_step, abs(y));
      }else if (current_speed > abs(y)){
        current_speed = max(current_speed - speed_step, abs(y));
      }
      analogWrite(RPWM2, abs(current_speed));
      delay(10);
    }
  }
  else if (y > 0) {
    while (current_speed != y)
    {
      if (current_speed < y)
      {
        current_speed = min(current_speed + speed_step, y);
      }else if (current_speed > y){
        current_speed = max(current_speed - speed_step, y);
      }
      analogWrite(LPWM2, current_speed);
      delay(10);
    }
  }
  else {
    while (current_speed != y)
    {
      if (current_speed < y)
      {
        current_speed = min(current_speed + speed_step, y);
      }else if (current_speed > y){
        current_speed = max(current_speed - speed_step, y);
      }
      analogWrite(LPWM2, current_speed);
      analogWrite(RPWM2, current_speed);
      delay(10);
    }
  }
}

void motor3(int z)
{
  int current_speed = 0;
  int stepping_speed = 20;
  if (z < 0){
    while (current_speed != abs(z))
    {
      if (current_speed < abs(z))
      {
        current_speed = min(current_speed + speed_step, abs(z));
      }else if (current_speed > abs(z)){
        current_speed = max(current_speed - speed_step, abs(z));
      }
      analogWrite(RPWM3, abs(current_speed));
      delay(10);
    }
  }
  else if (z > 0) {
    while (current_speed != z)
    {
      if (current_speed < z)
      {
        current_speed = min(current_speed + speed_step, z);
      }else if (current_speed > z){
        current_speed = max(current_speed - speed_step, z);
      }
      analogWrite(LPWM3, current_speed);
      delay(10);
    }
  }
  else {
    while (current_speed != z)
    {
      if (current_speed < z)
      {
        current_speed = min(current_speed + speed_step, z);
      }else if (current_speed > z){
        current_speed = max(current_speed - speed_step, abs(z));
      }
      analogWrite(LPWM3, current_speed);
      analogWrite(RPWM3, current_speed);
      delay(10);
    }
  }
}

void jalan(int target_speed){
  int current_speed = 0;
  int stepping_speed = 20;
  while (current_speed != target_speed)
  {
    if (current_speed < target_speed)
    {
      current_speed = min(current_speed + speed_step, target_speed);
    }else if (current_speed > target_speed){
      current_speed = max(current_speed - speed_step, target_speed);
    }
    delay(10);
  }
  
  
}
