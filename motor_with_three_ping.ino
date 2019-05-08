const int pingPin = 7; //mid sensor is pin 7
const int pingPin1 = 10; //right sensor pin 10
const int pingPin2_trig = 2; // trigger left sensor 
const int pingPin2_echo = 3; // echo left sensor 
int objectDetectedMid;
int objectDetectedLeft;
int objectDetectedRight; 
void Distance_Init();
int getDistanceMid();
int getDistanceLeft();
int getDistanceRight();
void Motor_Forward();
void Motor_Reverse();
void Motor_Stop();
void Turn_Left();
void Turn_Right();
void AvoidObjectMid();
void AvoidObjectLeft();
void AvoidObjectRight();
void checkDistance(); 
long duration, inches, cm;
int distancemid;
int distanceleft; 
int distanceright; 

#define MOTOR_L_SLP_PIN 31  // <- Energia Pin #   Launchpad Pin -> P3.7
#define MOTOR_L_DIR_PIN 14  // <- Energia Pin #   Launchpad Pin -> P1.7
#define MOTOR_L_PWM_PIN 40  // <- Energia Pin #   Launchpad Pin -> P2.7
#define MOTOR_R_SLP_PIN 11  // <- Energia Pin #   Launchpad Pin -> P3.6
#define MOTOR_R_DIR_PIN 15  // <- Energia Pin #   Launchpad Pin -> P1.6
#define MOTOR_R_PWM_PIN 39  // <- Energia Pin #   Launchpad Pin -> P2.6


void setup() {
  // put your setup code here, to run once:
  pinMode(MOTOR_L_DIR_PIN, INPUT);
  pinMode(MOTOR_R_DIR_PIN, INPUT);
  pinMode(MOTOR_L_SLP_PIN, INPUT);
  pinMode(MOTOR_R_SLP_PIN, INPUT);
  pinMode(MOTOR_L_PWM_PIN, INPUT);
  pinMode(MOTOR_R_PWM_PIN, INPUT);
  Serial.begin(9600);
}

long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}



int getDistanceMid(){ 

  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  Serial.print("mid: ");
  Serial.print(inches);
  Serial.print("in, ");
  Serial.println();

  delay(100);

  return inches; 
}


int getDistanceRight(){
  
  pinMode(pingPin1, OUTPUT);
  digitalWrite(pingPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin1, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin1, LOW);
  
  pinMode(pingPin1, INPUT);
  duration = pulseIn(pingPin1, HIGH);

  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  Serial.print("right: ");
  Serial.print(inches);
  Serial.print("in, ");
  Serial.println();

  delay(100);

  return inches; 
  
}

int getDistanceLeft(){
  
  pinMode(pingPin2_echo, INPUT);
  pinMode(pingPin2_trig, OUTPUT);
  digitalWrite(pingPin2_trig, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin2_trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(pingPin2_trig, LOW);
  
  duration = pulseIn(pingPin2_echo, HIGH);

  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  Serial.print("left: ");
  Serial.print(inches);
  Serial.print("in, ");
  Serial.println();

  delay(100);

  return inches; 
}

void checkDistance(){
  
  distancemid = getDistanceMid();
  distanceleft = getDistanceLeft();
  distanceright = getDistanceRight();

  //check middle ping

  if(distancemid < 10){
    objectDetectedMid = 1;
  }
  else{
    objectDetectedMid = 0;
  }

  if(distanceleft < 10){
    objectDetectedLeft = 1;
  }else{
    objectDetectedLeft = 0;
  }

  if(distanceright < 10){
    objectDetectedRight = 1;
  }else{
    objectDetectedRight  = 0;
  }
}
void Motor_Forward(){
  digitalWrite(MOTOR_L_DIR_PIN, 0);
  digitalWrite(MOTOR_R_DIR_PIN, 0);
  analogWrite(MOTOR_L_PWM_PIN, 50);
  analogWrite(MOTOR_R_PWM_PIN, 50);

  delay(100);

  
}

void Motor_Reverse(){
  Serial.print("reverse");
  Serial.println();
  digitalWrite(MOTOR_L_DIR_PIN, 1);
  digitalWrite(MOTOR_R_DIR_PIN, 1);
  analogWrite(MOTOR_L_PWM_PIN, 50);
  analogWrite(MOTOR_R_PWM_PIN, 50);

  delay(100);


}

void Turn_Left(){
   digitalWrite(MOTOR_R_DIR_PIN, 1);
   digitalWrite(MOTOR_L_SLP_PIN, 1);
   analogWrite(MOTOR_R_PWM_PIN, 50);
}

void Turn_Right(){
   digitalWrite(MOTOR_L_DIR_PIN, 1);
   digitalWrite(MOTOR_R_SLP_PIN, 1);
   analogWrite(MOTOR_R_PWM_PIN, 50);
}

void Motor_Stop(){
   digitalWrite(MOTOR_L_DIR_PIN, 0);
   digitalWrite(MOTOR_R_SLP_PIN, 0);
}


void AvoidObjectMid(){

  if(distanceleft < distanceright){
    Turn_Right();
  }else{
    Turn_Left();
  }

  while(objectDetectedMid == 1){
    checkDistance(); //i think this should be here, wasn't in the code online 
  }

  Motor_Stop();

  delay(250);
  
}

void AvoidObjectLeft(){

  Motor_Stop();
  Turn_Right();

  while(objectDetectedLeft == 1){
    checkDistance();  //i think this should be here, wasn't in the code online 
  }

  Motor_Stop();
  delay(250);
}

void AvoidObjectRight(){

  Motor_Stop();
  delay(250);
  Turn_Left();

  while(objectDetectedRight == 1){
    checkDistance();
  }

  Motor_Stop();
  delay(250);
  
  
}
void loop() {
  // put your main code here, to run repeatedly: 

   checkDistance(); //gets the distance of all ping sensors and sets value of objectDetected
   

  while(1)
  {

    if(objectDetectedMid == 1){
      Serial.print("objMid: ");
      Serial.print(objectDetectedMid);
      AvoidObjectMid();
      delay(250);
    }
    else if(objectDetectedLeft == 1){
      Serial.print("objLeft: ");
      Serial.print(objectDetectedLeft);
      AvoidObjectLeft();
      delay(250);
    }
    else if (objectDetectedRight == 1){
      Serial.print("objRight: ");
      Serial.print(objectDetectedRight);
      AvoidObjectRight();
      delay(250);
    }
    else{
      Motor_Forward();
    }
  }
}
