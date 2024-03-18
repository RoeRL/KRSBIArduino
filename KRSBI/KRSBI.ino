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
int RPWM1 = 7;  // Digital/PWM pin 5 to the RPWM on the BTS7960
int LPWM1 = 6;  // Digital/PWM pin 6 to the LPWM on the BTS7960
// Enable "Left" and "Right" movement for the first wheel

int RPWM2 = 5;  // Digital/PWM pin 5 to the RPWM on the BTS7960
int LPWM2 = 4;  // Digital/PWM pin 6 to the LPWM on the BTS7960
// Enable "Left" and "Right" movement for the second wheel

int RPWM3 = 3;  // Digital/PWM pin 5 to the RPWM on the BTS7960
int LPWM3 = 2;  // Digital/PWM pin 6 to the LPWM on the BTS7960
// Enable "Left" and "Right" movement for the third wheel



void setup() {
  // put your setup code here, to run once:

  // initialize all our pins to output
  for (int i = 4; i < 29; i++) {
    pinMode(i, OUTPUT);
  }
  delay(1000);// wait a second
  Serial.begin(9600);
  stop();
  
  //enable "Right" and "Left" movement on the HBridge
  // Notice use of digitalWrite to simply turn it on and keep it on.
}



void loop() {
  // put your main code here, to run repeatedly:

  // Use an analogWrite(pin,  which tells it to send a modulated
  // signal (PWM) to specific pin at a specific "duty cycle".
  // Valid values are 0 to 255.  0 means always off(or no power) and 255 means always on(full power)
  // https://www.arduino.cc/reference/en/language/functions/analog-io/analogwrite/// wait 5 seconds, motor continues to move because the analogWrite is still pulsing
  forward();
  delay(1000);
  stop();
  delay(1000);

  backward();
  delay(1000);
  stop();
  delay(1000);

  right();
  delay(1000);
  stop();
  delay(1000);

}

void forward(){
  analogWrite(RPWM1, 255);
  analogWrite(LPWM2, 255);
}

void backward(){
  analogWrite(LPWM1, 255);
  analogWrite(RPWM2, 255);
}

void right(){
  analogWrite(RPWM1, 255);
  analogWrite(RPWM2, 255);
  analogWrite(LPWM3, 255);
}

void left(){
  analogWrite(LPWM1, 255);
  analogWrite(LPWM2, 255);
  analogWrite(RPWM3, 255);
}

void stop(){
  analogWrite(LPWM1, 0);
  analogWrite(LPWM2, 0);
  analogWrite(LPWM3, 0);
  analogWrite(RPWM1, 0);
  analogWrite(RPWM2, 0);
  analogWrite(RPWM3, 0);
}
