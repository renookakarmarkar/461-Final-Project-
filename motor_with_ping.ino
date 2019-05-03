const int pingPin = 7;
int objectDetected;
void Distance_Init();
int getDistance();
void Motor_Forward();
void Motor_Reverse();
void Turn_Left();
void Turn_Right();
void AvoidObject();
long duration, inches, cm;
int distance;

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



int getDistance(){ 

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

  Serial.print(inches);
  Serial.print("in, ");
  Serial.println();

  delay(100);

  return inches; 
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


void AvoidObject(){

  Serial.print("in avoidObject");
    Serial.println();

  distance = getDistance();
  
  if (distance < 10){
    //object too close
    objectDetected  = 1;
    Serial.print("too close");
    Serial.println();
    Motor_Reverse();

    delay(200);

    //return objectDetected;
  }
  else
  {
    Serial.print("too far");
    objectDetected = 0;

    //return objectDetected;
  }
  
  
}
void loop() {
  // put your main code here, to run repeatedly: 


  while(1)
  {
    Serial.print("ObjVal: ");
    Serial.print(objectDetected);
    Serial.println();
    AvoidObject();
    Serial.print("ObjValAfter: ");
    Serial.print(objectDetected);
    Serial.println();
    if(objectDetected == 0){
      Serial.println("forward");
      Serial.println();
      Motor_Forward();
    }
    else{
      AvoidObject();
      delay(200);
    }
  }
}
