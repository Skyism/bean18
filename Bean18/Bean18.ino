#include <WiiChuck.h>

Accessory nunchuck1;

double y = 0;
double x = 0;
double mag = .5;
bool c = false;
bool z = false;

int pwmFR = 37; // unchanged
int brakeFR = 39; // unchanged
int reverseFR = 41; // unchanged 
int pwmFL = 31; // unchanged
int brakeFL = 35; // unchanged
int reverseFL = 33; // unchanged
int pwmBR = 43; // unchanged
int brakeBR = 45; // unchanged
int reverseBR = 47; // unchanged 
int pwmBL = 49; // unchanged
int brakeBL = 51; // unchanged
int reverseBL = 53; // unchanged

void setup() {
  pinMode(reverseFR, OUTPUT);
  pinMode(brakeFR, OUTPUT);
  pinMode(reverseFL, OUTPUT);
  pinMode(brakeFL, OUTPUT);
  pinMode(reverseBR, OUTPUT);
  pinMode(brakeBR, OUTPUT);
  pinMode(reverseBL, OUTPUT);
  pinMode(brakeBL, OUTPUT);
  Serial.begin(9600);
  nunchuck1.begin();
	if (nunchuck1.type == Unknown) {
		/** If the device isn't auto-detected, set the type explicatly
		 * 	NUNCHUCK,
		 WIICLASSIC,
		 GuitarHeroController,
		 GuitarHeroWorldTourDrums,
		 DrumController,
		 DrawsomeTablet,
		 Turntable
		 */
		nunchuck1.type = NUNCHUCK;
	}
  Serial.println("Starting");
}

void loop() {
	nunchuck1.readData();
  z = nunchuck1.values[10] >= 127.5;
  c = nunchuck1.values[11] >= 127.5;
  x = ((double)nunchuck1.values[0] / 127.5) - 1.0;
  y = (((double)nunchuck1.values[1] / 127.5) - 1.0);
  
  if(abs(x) < .1){
      x = 0;
  }
  if(abs(y) < .1){
     y = 0;
  }
  
  if(c){
    mag = .5;
  }else{
    mag = .25;
  }
  //left
  //Serial.println((mag * (double)255) * (y + x));
  setMotorSpdFL((mag * (double)255) * (y + x), z);
  setMotorSpdBL((mag * (double)255) * (y + x), z);
  //right
  setMotorSpdFR((mag * (double)255) * (y - x), z);
  setMotorSpdBR((mag * (double)255) * (y - x), z);
}
void setMotorSpdFL(float spd, bool brake){
  if(spd < 0){
     digitalWrite(reverseFL, HIGH);
  }else{
    digitalWrite(reverseFL, LOW);
  }
  if(brake){
     digitalWrite(brakeFL, HIGH);
  }else{
    digitalWrite(brakeFL, LOW);
  }
  analogWrite(pwmFL, abs(spd));
}
void setMotorSpdBL(float spd, bool brake){
  if(spd < 0){
     digitalWrite(reverseBL, HIGH);
  }else{
    digitalWrite(reverseBL, LOW);
  }
  if(brake){
     digitalWrite(brakeBL, HIGH);
  }else{
    digitalWrite(brakeBL, LOW);
  }
  analogWrite(pwmBL, abs(spd));
}
void setMotorSpdFR(float spd, bool brake){
  if(spd < 0){
     digitalWrite(reverseFR, HIGH);
  }else{
    digitalWrite(reverseFR, LOW);
  }
  if(brake){
     digitalWrite(brakeFR, HIGH);
  }else{
    digitalWrite(brakeFR, LOW);
  }
  analogWrite(pwmFR, abs(spd));
}
void setMotorSpdBR(float spd, bool brake){
  if(spd < 0){
     digitalWrite(reverseBR, HIGH);
  }else{
    digitalWrite(reverseBR, LOW);
  }
  if(brake){
     digitalWrite(brakeBR, HIGH);
  }else{
    digitalWrite(brakeBR, LOW);
  }
  analogWrite(pwmBR, abs(spd));
}
