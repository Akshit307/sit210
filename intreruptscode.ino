const int switchPin = 2;     
const int led1Pin = 8;       
const int trigPin = 4;       
const int echoPin = 5;       
const int led2Pin = 9;       

volatile bool led1State = false;  
bool led2State = false;          

void handleSwitch() {
  led1State = !led1State;
  digitalWrite(led1Pin, led1State);
  Serial.println("LED1 toggled!");
}

void setup() {
  Serial.begin(9600);

  pinMode(switchPin, INPUT);         
  pinMode(led1Pin, OUTPUT);          
  pinMode(trigPin, OUTPUT);          
  pinMode(echoPin, INPUT);           
  pinMode(led2Pin, OUTPUT);      

  attachInterrupt(digitalPinToInterrupt(switchPin), handleSwitch, CHANGE);
}

void loop() {
  // Send trigger pulse to HC-SR04
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  
  long duration = pulseIn(echoPin, HIGH, 25000);  
  float distance = (duration * 0.0343) / 2;       


  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");


  if (distance > 0 && distance < 20) {
    if (!led2State) {
      digitalWrite(led2Pin, HIGH);
      led2State = true;
      Serial.println("Object detected: LED2 ON");
    }
  } else {
    if (led2State) {
      digitalWrite(led2Pin, LOW);
      led2State = false;
      Serial.println("No object: LED2 OFF");
    }
  }

  delay(200); 
}
