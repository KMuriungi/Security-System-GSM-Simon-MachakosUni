int ledGreen = 13;                // choose the pin for the LED
int pirPin = 7;               // choose the input pin (for PIR sensor)            
int pirState = 0;                    

void setup() {
  pinMode(ledGreen, OUTPUT);      // declare LED as output
  pinMode(pirPin, INPUT);     // declare sensor as input

  Serial.begin(9600);
}

void loop(){
  pirState = digitalRead(pirPin);  // read input pirStateue

  if (pirState == HIGH) {            // check if the input is HIGH
    digitalWrite(ledGreen, HIGH);  // turn LED ON  
     
    Serial.print("PIR State: ");
    Serial.println(pirState);

  } else {
    digitalWrite(ledGreen, LOW); // turn LED OFF
    
      Serial.print("PIR State: ");
      Serial.println(pirState);

    }
  }
