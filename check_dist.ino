
void setup(){

}

void loop(){
  while(1)
  {
    checkDistance();
  }
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
  
  pinMode(pingPin2, OUTPUT);
  digitalWrite(pingPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin2, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin2, LOW);
  
  pinMode(pingPin2, INPUT);
  duration = pulseIn(pingPin2, HIGH);

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

  //check left ping
  if(distanceleft < 10){
    objectDetectedLeft = 1;
  }else{
    objectDetectedLeft = 0;
  }

  //check right ping 
  if(distanceright < 10){
    objectDetectedRight = 1;
  }else{
    objectDetectedRight  = 0;
  }
}
