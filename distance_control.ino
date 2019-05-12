const int pingPin = 7; //mid sensor is pin 7 -> P4.6
long duration, inches, cm;
int dist();
void Motor_Forward();
void Motor_Reverse();
void Motor_Stop();
void Motor_Enable();
void Turn_Left();
void Turn_Right();
int setPoint = 10; 
int error;
int kp;
int distance, speed; 

#define MOTOR_L_SLP_PIN 31  // <- Energia Pin #   Launchpad Pin -> P3.7
#define MOTOR_L_DIR_PIN 14  // <- Energia Pin #   Launchpad Pin -> P1.7
#define MOTOR_L_PWM_PIN 40  // <- Energia Pin #   Launchpad Pin -> P2.7
#define MOTOR_R_SLP_PIN 11  // <- Energia Pin #   Launchpad Pin -> P3.6
#define MOTOR_R_DIR_PIN 15  // <- Energia Pin #   Launchpad Pin -> P1.6
#define MOTOR_R_PWM_PIN 39  // <- Energia Pin #   Launchpad Pin -> P2.6

void setup() {
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

int dist(){ 

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

  Serial.print("inches: ");
  Serial.print(inches);
  //Serial.print("in, ");
  Serial.println();

  delay(100);

  return inches; 
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
   analogWrite(MOTOR_R_PWM_PIN, 30);
   analogWrite(MOTOR_L_PWM_PIN, 70);

   delay(3000);
}

void Motor_Stop(){
   digitalWrite(MOTOR_L_SLP_PIN, LOW);
   digitalWrite(MOTOR_R_SLP_PIN, LOW);

   delay(1000); 
}

void loop() {
  // put your main code here, to run repeatedly: 
  Motor_Enable(); 
  while(1){
      Motor_Enable();
      distance  = dist();
      error = setPoint  - distance; 
      if(setPoint > distance)
      {
        digitalWrite(MOTOR_L_DIR_PIN, HIGH);
        digitalWrite(MOTOR_R_DIR_PIN, HIGH);
        kp = 10;
        if((kp * error) < 90){
        speed  = kp * error;

        analogWrite(MOTOR_R_PWM_PIN, speed);
        analogWrite(MOTOR_L_PWM_PIN, speed);
        Serial.print("speed: ");
        Serial.print(speed);
        Serial.println();
        Serial.print("error: ");
        Serial.print(error);
        Serial.println();
        Serial.print("distance: ");
        Serial.print(distance);
        
        }
      }
      else if(setPoint < distance){
        Motor_Enable();
        digitalWrite(MOTOR_L_DIR_PIN, LOW);
        digitalWrite(MOTOR_R_DIR_PIN, LOW);
        kp = -10;
        if((kp * error) < 90){
        speed  = kp * error;
        
        Serial.print("speed: ");
        Serial.print(speed);
        Serial.println();
        Serial.print("error: ");
        Serial.print(error);
        Serial.print("distance: ");
        Serial.print(distance);
        analogWrite(MOTOR_R_PWM_PIN, speed);
        analogWrite(MOTOR_L_PWM_PIN, speed);
        }
      }
      else{

        Serial.print("stop");
        Motor_Stop(); 
      }
    

  }
  
}
