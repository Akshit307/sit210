#define SWITCH_PIN 2
#define TRIG_PIN   8
#define ECHO_PIN   3
#define LED1_PIN   5
#define LED2_PIN   6
#define LED3_PIN   7

volatile bool led2State = false;
bool led1State = false;
bool led3State = false;
int lastSwitchState = HIGH;
unsigned long lastBlink = 0;
const unsigned long interval = 1000; 

void echoISR() {
  led2State = !led2State;
  digitalWrite(LED2_PIN, led2State);
  Serial.println(">> Ultrasonic: LED2 toggled");
}

void setup() {
  Serial.begin(115200);
  while (!Serial);

  Serial.println("=== SYSTEM STARTED ===");

  pinMode(SWITCH_PIN, INPUT_PULLUP);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT_PULLUP);

  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);
  pinMode(LED3_PIN, OUTPUT);

  digitalWrite(LED1_PIN, LOW);
  digitalWrite(LED2_PIN, LOW);
  digitalWrite(LED3_PIN, LOW);

  attachInterrupt(digitalPinToInterrupt(ECHO_PIN), echoISR, FALLING);
}

void loop() {
  
  int currentSwitchState = digitalRead(SWITCH_PIN);
  if (lastSwitchState == HIGH && currentSwitchState == LOW) {
    led1State = !led1State;
    digitalWrite(LED1_PIN, led1State);
    Serial.println(">> Switch: LED1 toggled");
    delay(200); 
  }
  lastSwitchState = currentSwitchState;

 
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  delay(100);

 
  if (millis() - lastBlink >= interval) {
    led3State = !led3State;
    digitalWrite(LED3_PIN, led3State);
    Serial.println(">> Timer (millis): LED3 toggled");
    lastBlink = millis();
  }
}
