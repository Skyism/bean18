//test

double y = 0;
double x = 0;
double mag = .5;
bool c = false;
bool z = false;

double breakCutoff = 3;

int pwmR = 10; // unchanged
int brakeR = 5; // unchanged
int reverseR = 4; // unchanged 
int pwmL = 9; // unchanged
int brakeL = 3; // unchanged
int reverseL = 2; // unchanged

void setup() {
  pinMode(reverseR, OUTPUT);
  pinMode(brakeR, OUTPUT);
  pinMode(reverseL, OUTPUT);
  pinMode(brakeL, OUTPUT);
  delay(3000);
  Serial.begin(9600);
}

void loop() {
  
  //left
  setMotorSpdL((mag * (double)255) * (y + x));
  //right
  setMotorSpdR((mag * (double)255) * (y - x));
}
void setMotorSpdL(float spd){
  if(spd < 0){
     digitalWrite(reverseL, HIGH);
  }else{
    digitalWrite(reverseL, LOW);
  }
  if(abs(spd) < breakCutoff && rd < .5){
     digitalWrite(brakeL, HIGH);
  }else{
    digitalWrite(brakeL, LOW);
  }
  analogWrite(pwmL, abs(spd));
}
void setMotorSpdR(float spd){
  if(spd < 0){
     digitalWrite(reverseR, LOW);
  }else{
    digitalWrite(reverseR, HIGH);
  }
  if(abs(spd) < breakCutoff && rd < .5){
     digitalWrite(brakeR, HIGH);
  }else{
    digitalWrite(brakeR, LOW);
  }
  analogWrite(pwmR, abs(spd));
}