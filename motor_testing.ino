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
}

void loop() {

  //Left wheel forward
  digitalWrite(MOTOR_L_DIR_PIN, 1);
  digitalWrite(MOTOR_R_SLP_PIN, 1);
  analogWrite(MOTOR_L_PWM_PIN, 50);
  
  delay(5000);


  //Both forward
  digitalWrite(MOTOR_L_DIR_PIN, 1);
  digitalWrite(MOTOR_R_DIR_PIN, 1);
  analogWrite(MOTOR_L_PWM_PIN, 50);
  analogWrite(MOTOR_R_PWM_PIN, 50);

  delay(10000);

  //Both Backwards
  digitalWrite(MOTOR_L_DIR_PIN, 0);
  digitalWrite(MOTOR_R_DIR_PIN, 0);
  analogWrite(MOTOR_L_PWM_PIN, 50);
  analogWrite(MOTOR_R_PWM_PIN, 50);

  delay(10000);

  //Turn left
  digitalWrite(MOTOR_R_DIR_PIN, 1);
  digitalWrite(MOTOR_L_SLP_PIN, 1);
  analogWrite(MOTOR_R_PWM_PIN, 50);
  
  delay(10000);

  //Turn Right
  digitalWrite(MOTOR_L_DIR_PIN, 1);
  digitalWrite(MOTOR_R_SLP_PIN, 1);
  analogWrite(MOTOR_R_PWM_PIN, 50);

  delay(5000);
}
 
