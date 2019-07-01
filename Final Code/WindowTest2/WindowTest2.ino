int led= 40;
int winPin = 4;
int winState;

void setup() {
  pinMode(winPin, INPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  winState = digitalRead(winPin);
  Serial.println(winState);
  digitalWrite(led, winState);
}
