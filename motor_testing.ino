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

void loop() {

  //enable motors 
  digitalWrite(MOTOR_L_SLP_PIN, HIGH);
  digitalWrite(MOTOR_R_SLP_PIN, HIGH);
  
  //set speed 
  analogWrite(MOTOR_L_PWM_PIN, 25);
  analogWrite(MOTOR_R_PWM_PIN, 25);
  
  //Both forward
  Serial.print("forward");
  Serial.println();
  digitalWrite(MOTOR_L_DIR_PIN, LOW);
  digitalWrite(MOTOR_R_DIR_PIN, LOW);

  delay(5000);

  digitalWrite(MOTOR_L_SLP_PIN, LOW);
  digitalWrite(MOTOR_R_SLP_PIN, LOW);

  delay(5000);

  //Turn Right
  Serial.print("right");
  Serial.println();
  digitalWrite(MOTOR_L_SLP_PIN, HIGH);
  digitalWrite(MOTOR_R_SLP_PIN, HIGH);
  analogWrite(MOTOR_R_PWM_PIN, 25);
  analogWrite(MOTOR_L_PWM_PIN, 40);

  delay(5000);

  digitalWrite(MOTOR_L_SLP_PIN, LOW);
  digitalWrite(MOTOR_R_SLP_PIN, LOW);

  delay(5000);

   
  //Turn left
  Serial.print("left");
  Serial.println();
  digitalWrite(MOTOR_L_SLP_PIN, HIGH);
  digitalWrite(MOTOR_R_SLP_PIN, HIGH);
  analogWrite(MOTOR_L_PWM_PIN, 25);
  analogWrite(MOTOR_R_PWM_PIN, 40);
  delay(5000);

  digitalWrite(MOTOR_L_SLP_PIN, LOW);
  digitalWrite(MOTOR_R_SLP_PIN, LOW);

  delay(5000);
}
 
