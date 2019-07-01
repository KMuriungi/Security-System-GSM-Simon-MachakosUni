int led= 40;
int winPin = 4;
int winState = 0;

void setup() {
  pinMode(winPin, INPUT);
  pinMode(led, OUTPUT);
}

void loop(){
  winState = digitalRead(winPin);

 if (winState == HIGH){
  digitalWrite(led, HIGH);
  //delay(2000);
 }else {
  digitalWrite(led, LOW);
  //delay(2000);
  }
  delay(1000);
}
