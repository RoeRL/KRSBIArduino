/*
 * rosserial Publisher Example
 * Prints "hello world!"
 */

#include <ros.h>
#include <std_msgs/Float32.h>
//encoder messages
#include <encoder.h>

//encoder enco;

#define ENCA1 5
#define ENCB1 4
#define ENCA2 0
#define ENCB2 2
#define ENCA3 14
#define ENCB3 12

volatile int pos1 = 0;
volatile int pos2 = 0;
volatile int pos3 = 0;

ros::NodeHandle  nh;

robot_tf_pkg::encoder fl_msg;
ros::Publisher chatter("enco_value", &fl_msg);

void ICACHE_RAM_ATTR mot1(){
  int b = digitalRead(ENCB1);
  if (b>0){
    pos1++;
  }
  else{
    pos1--;
  }
  
}

void ICACHE_RAM_ATTR mot2(){
  int b = digitalRead(ENCB2);
  if (b>0){
    pos2++;
  }
  else{
    pos2--;
  }
  
}


void ICACHE_RAM_ATTR mot3(){
  int b = digitalRead(ENCB3);
  if (b>0){
    pos3++;
  }
  else{
    pos3--;
  }
  
}

void setup()
{
  jalan1();
  jalan2();
  jalan3();
  Serial.begin(115200);
  nh.initNode();
  nh.advertise(chatter);
}

void loop()
{
//  pos1 = 2*3.14*50*(pos1/135);
//  pos2 = 2*3.14*50*(pos2/135);
//  pos3 = 2*3.14*50*(pos3/135);
  fl_msg.enc1 = pos1;
  fl_msg.enc2 = pos2;
  fl_msg.enc3 = pos3;
  chatter.publish( &fl_msg );
  nh.spinOnce();
  delay(1);
}

void jalan1(){
  pinMode(ENCA1, INPUT);
  pinMode(ENCB1, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCA1), mot1, RISING);
}
void jalan2(){
  pinMode(ENCA2, INPUT);
  pinMode(ENCB2, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCA2), mot2, RISING);
}
void jalan3(){
  pinMode(ENCA3, INPUT);
  pinMode(ENCB3, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCA3), mot3, RISING);
}
