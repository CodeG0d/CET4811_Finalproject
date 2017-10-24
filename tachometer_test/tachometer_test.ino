const int TACH_PIN = A0; 

void setup() {
  pinMode(TACH_PIN, INPUT);
  digitalWrite(TACH_PIN, HIGH);
  Serial.begin(9600);
}

void loop() {
  Serial.println(digitalRead(TACH_PIN));
}
