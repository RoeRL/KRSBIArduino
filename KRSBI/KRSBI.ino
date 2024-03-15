/*......................
 *  BTS7960 HBridge Test
 *  
 *  Simple example of using the BTS7960 HBridge to control a motor
 *  This sketch simply sends a pwm signal to the HBridge to spin the motor 
 *  one way and then spin the motor the other direction.
 *  
 *  PWM Description for Arduino: https://www.arduino.cc/en/tutorial/PWM
 *  
 *  By : Barry Tarlton
*/
// Set the pin out for the Right PWM and Left PWM
// "Right" and "Left" are relative to the motor direction and 
// doesn't make sense from a programming point of view sense 
// depending on how you wire or physcally mount the motor the direction is different.
// But when you send a signal on RPWM the motor will go one way and when you 
// send a signal on LPWM, the motor will go the other way.
int RPWM1 = 4;  // Digital/PWM pin 5 to the RPWM on the BTS7960
int LPWM1 = 5;  // Digital/PWM pin 6 to the LPWM on the BTS7960
// Enable "Left" and "Right" movement for the first wheel
int L_EN1 = 20;  // connect Digital/PWM pin 7 to L_EN on the BTS7960
int R_EN1 = 21;  // connect Digital/PWM pin 8 to R_EN on the BTS7960

int RPWM2 = 6;  // Digital/PWM pin 5 to the RPWM on the BTS7960
int LPWM2 = 7;  // Digital/PWM pin 6 to the LPWM on the BTS7960
// Enable "Left" and "Right" movement for the second wheel
int L_EN2 = 22;  // connect Digital/PWM pin 7 to L_EN on the BTS7960
int R_EN2 = 24;  // connect Digital/PWM pin 8 to R_EN on the BTS7960

int RPWM3 = 8;  // Digital/PWM pin 5 to the RPWM on the BTS7960
int LPWM3 = 9;  // Digital/PWM pin 6 to the LPWM on the BTS7960
// Enable "Left" and "Right" movement for the third wheel
int L_EN3 = 26;  // connect Digital/PWM pin 7 to L_EN on the BTS7960
int R_EN3 = 28;  // connect Digital/PWM pin 8 to R_EN on the BTS7960



void setup() {
  // put your setup code here, to run once:

  // initialize all our pins to output
  for (int i = 4; i < 29; i++) {
    pinMode(i, OUTPUT);
  }
  // set all the pins you want to use to LOW
  for (int i = 4; i < 29; i++) {
    digitalWrite(i, LOW);
  }
  delay(1000);// wait a second
  Serial.begin(9600);
  
  //enable "Right" and "Left" movement on the HBridge
  // Notice use of digitalWrite to simply turn it on and keep it on.
  digitalWrite(R_EN1, HIGH);  
  digitalWrite(L_EN1, HIGH);
  digitalWrite(R_EN2, HIGH);  
  digitalWrite(L_EN2, HIGH);
  digitalWrite(R_EN3, HIGH);  
  digitalWrite(L_EN3, HIGH);
}



void loop() {
  // put your main code here, to run repeatedly:

  // Use an analogWrite(pin,  which tells it to send a modulated
  // signal (PWM) to specific pin at a specific "duty cycle".
  // Valid values are 0 to 255.  0 means always off(or no power) and 255 means always on(full power)
  // https://www.arduino.cc/reference/en/language/functions/analog-io/analogwrite/// wait 5 seconds, motor continues to move because the analogWrite is still pulsing
  analogWrite(RPWM, 128); // pulse signal now at 128 (about half power... half of max 255).


  // after 5 seconds at half power, stop the motor moving
  analogWrite(RPWM, 0);
  delay(1000);
  // now start moving in opposite direction.
  analogWrite(LPWM, 64);
  delay(1000);
  analogWrite(LPWM, 128);
  delay(1000);
  analogWrite(LPWM, 0); // Stop moving in this direction
  // at this point should be no movement.
  
  delay(1000);
}

void forward(){
  analogWrite(RWPM1, 128);
  analogWrite(LWPM2, 128);
}

void backward(){
  analogWrite(LPWM1, 128);
  analogWrite(RWPM2, 128);
}

void right(){
  analogWrite(RPWM1, 128);
  analogWrite(RPWM2, 128);
  analogWrite(LPWM3, 128);
}

void left(){
  analogWrite(LPWM1, 128);
  analogWrite(LPWM2, 128);
  analogWrite(RWPM3, 128);
}

void stop(){
  analogWrite(LPWM1, 0);
  analogWrite(LPWM2, 0);
  analogWrite(LWPM3, 0);
  analogWrite(RWPM1, 0);
  analogWrite(RWPM2, 0);
  analogWrite(RWPM3, 0);
}
