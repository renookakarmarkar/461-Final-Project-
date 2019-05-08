const int pingPin = 7; //mid sensor is pin 7 -> P4.6
const int pingPin1 = 10; //right sensor pin 10 ->P1.5 
const int pingPin2 = 3; // left sensor pin 3 -> P3.2 
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
void Motor_Enable();
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


void Motor_Enable(){
  digitalWrite(MOTOR_L_SLP_PIN, HIGH);
  digitalWrite(MOTOR_R_SLP_PIN, HIGH);
}

void Motor_Forward(){
  Motor_Enable();
  analogWrite(MOTOR_L_PWM_PIN, 30);
  analogWrite(MOTOR_R_PWM_PIN, 30);
  digitalWrite(MOTOR_L_DIR_PIN, LOW);
  digitalWrite(MOTOR_R_DIR_PIN, LOW);

  delay(3000);
}

void Motor_Reverse(){
  Serial.print("reverse");
  Serial.println();
  Motor_Enable();
  analogWrite(MOTOR_L_PWM_PIN, 30);
  analogWrite(MOTOR_R_PWM_PIN, 30);
  digitalWrite(MOTOR_L_DIR_PIN, HIGH);
  digitalWrite(MOTOR_R_DIR_PIN, HIGH);
  delay(3000);
}

void Turn_Left(){
  Motor_Enable();
  analogWrite(MOTOR_R_PWM_PIN, 70);
  analogWrite(MOTOR_L_PWM_PIN, 30);

  delay(3000);
}

void Turn_Right(){
   Motor_Enable();
   Serial.println("execute");
   analogWrite(MOTOR_R_PWM_PIN, 30);
   analogWrite(MOTOR_L_PWM_PIN, 70);

   delay(3000);
}

void Motor_Stop(){
   digitalWrite(MOTOR_L_SLP_PIN, LOW);
   digitalWrite(MOTOR_R_SLP_PIN, LOW);

   delay(1000); 
}


void AvoidObjectMid(){

  if(distanceleft < distanceright){
    Serial.print("mid turning right");
    Serial.println();
    Motor_Reverse();
    Motor_Stop();
    digitalWrite(MOTOR_L_DIR_PIN, LOW);
    digitalWrite(MOTOR_R_DIR_PIN, LOW);
    Turn_Right();
  }else{
    Serial.print("mid turning left");
    Serial.println();
    Motor_Reverse();
    Motor_Stop();
    digitalWrite(MOTOR_L_DIR_PIN, LOW);
    digitalWrite(MOTOR_R_DIR_PIN, LOW);
    Turn_Left();
  }

//  while(objectDetectedMid == 1){
//    //checkDistance already running 
//  }

  Serial.println("stop mid");
  Motor_Stop();
  
}

void AvoidObjectLeft(){

  Serial.println("stop left");
  Motor_Stop();
  Serial.print("turning right");
  Serial.println();
  Turn_Right();

//  while(objectDetectedLeft == 1){
//    //checkDistance already running 
//  }

  Motor_Stop();
}

void AvoidObjectRight(){

  Serial.println("stop right");
  Motor_Stop();
  delay(250);
  Serial.print("turning left");
  Serial.println();
  Turn_Left();

//  while(objectDetectedRight == 1){
//    //checkDistance already running 
//  }

  Motor_Stop();
}

void loop() {
  // put your main code here, to run repeatedly: 

   //checkDistance(); //gets the distance of all ping sensors and sets value of objectDetected
   
    //delay(500);

  
  while(1)
  {

   if(objectDetectedMid == 1){
      Serial.print("objMid: ");
      Serial.print(objectDetectedMid);
      AvoidObjectMid();
      //delay(250);
    }
    else if(objectDetectedLeft == 1){
      Serial.print("objLeft: ");
      Serial.print(objectDetectedLeft);
      AvoidObjectLeft();
      //delay(250);
    }
    else if (objectDetectedRight == 1){
      Serial.print("objRight: ");
      Serial.print(objectDetectedRight);
      AvoidObjectRight();
      //delay(250);
    }
    else{
      Motor_Forward();
    }
  }
}
