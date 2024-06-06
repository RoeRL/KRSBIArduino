int RPWM1 = 6;
int LPWM1 = 7;

int RPWM2 = 5;
int LPWM2 = 4;
                                                                                                                                                                                                                              
int RPWM3 = 2;
int LPWM3 = 3;

void setup(){
  // put your setup code here, to run once:
  pinMode(RPWM1, OUTPUT);
  pinMode(LPWM1, OUTPUT);
  pinMode(RPWM2, OUTPUT);
  pinMode(LPWM2, OUTPUT);
  pinMode(RPWM3, OUTPUT);
  pinMode(LPWM3, OUTPUT);
}

void loop() {
  int x = 100;
  int y = -100;
  int z = 0;
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
