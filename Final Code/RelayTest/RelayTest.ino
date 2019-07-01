void setup() {
  pinMode(5, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(5, HIGH);   
  delay(10000);                       // wait for a second
  digitalWrite(5, LOW);   
  delay(10000);                       // wait for a second
}
