/*
 * SECURITY SYSTEM - GSM Based With PIR
 * Arduino Controlled System
*/
/*
 ************************************************************
 *----------------------GSM LIBRARY-------------------------*
 ************************************************************
*/
#include <Sim800l.h>
Sim800l Sim800l;  //to declare the library
#include <SoftwareSerial.h> // Serial Library to enable Serial Comm'n

#include <SIM900.h>
#include <sms.h>
SMSGSM sms; 

//Included to help during initialiation process
//SIM900.h

boolean started = false;
char smsbuffer[160];
char n[20];


String textSms;
String numberSms;
uint8_t index; // to check the index position of the sms
bool error; // Boolean return to confirm True/False

/*
 ************************************************************
 *----------------------LCD LIBRARY-------------------------*
 ************************************************************
*/
#include<LiquidCrystal.h>  // Including LCD Library
LiquidCrystal lcd(9, 8, 14,15, 16, 17); //Configuring pins used 

/*
 ************************************************************
 *-------------------KEYPAD LIBRARY-------------------------*
 ************************************************************
*/
#include <Keypad.h> //Keypad Library

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns

//define the symbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {6, 5, 4, 3}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {14, 15, 16, 17}; //connect to the column pinouts of the keypad

//Initialize an instance of class NewKeypad : myKeypad
Keypad myKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

int keypadState;

/*
 ************************************************************
 *-----------------KEYPAD CHECK FUNCTION--------------------*
 ************************************************************
*
void keypadCheck()
{

String password = "A456#"; // SET Password verification 
String alfaCode;
int compareCODE( String alfaCode);    //We type a code on keypad and this will be 
  {                                 //compared with the password;
   if(alfaCode.equals(password))
   return 1; // VALID PASSWORD
   else 
   return 0; // INVALID PASSWORD
} //END compareCODE

char x;
String takeCode(char x); //Will display on the LCD when the Password is typed
  { char vec[10];
   vec[0] = x;
   lcd.clear();
   lcd.setCursor(3,0);
   lcd.print("PASSWORD:");
   lcd.setCursor(4,0);
   lcd.print('*');
   for(int i=1;i<6;i++)
      {
        vec[i] = myKeypad.waitForKey(); //Waits for 5 keys to be pressed and after that  
       lcd.print('*');                  //is taking the decision
       }               
       vec[6]=NULL;
       String str(vec);
       return str;
} //END takeCode

  char c = myKeypad.getKey();

  if(c != NO_KEY){
    String currentCode = takeCode(c);
    int A = compareCODE(currentCode);
    if(A == 0){         //A is a variable that stores the current code
       lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("INVALID CODE");
      
       delay(2000);
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("ACCESS DENIED");
        
        keypadState = 0;
       return;
    } //END if (A0)
  
    if(A == 1){
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print( "VALID CODE " );
        delay(2000);

        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("ACCESS GRANTED");

        keypadState = 1;
       return;
  
    } //END if (A1)
   }  // END if NO_KEY
  } //END  keypadCheck()

/*
 ************************************************************
 *-----------------CUSTOM DESIGN SYMBOL---------------------*
 ************************************************************
*/
// Designing a custom HEART Symbol ( Initialize the Function)
byte heart[8] = {
  0b00000,0b01010,0b11111,0b11111,0b11111,0b01110,0b00100,0b00000
};
// Designing a custom SMILEY Symbol ( Initialize the Function)
byte smiley[8] = { 
  0b00000,0b00000,0b01010,0b00000,0b00000,0b10001,0b01110,0b00000
};
// Designing a custom FROWNIE Symbol ( Initialize the Function)
byte frownie[8] = { 
  0b00000,0b00000,0b01010,0b00000,0b00000,0b00000,0b01110,0b10001
};
// Designing a custom ARMSDOWN Symbol ( Initialize the Function)
byte armsDown[8] = { 
  0b00100,0b01010,0b00100,0b00100,0b01110,0b10101,0b00100,0b01010
};

/*
 ************************************************************
 *----------------DECLARATION OF VARIABLES------------------*
 ************************************************************
*/

int pirPin = 3;
int pirState = LOW;             // we start, assuming no motion detected
int pirValue = 0;               // variable for reading the pin status

int magneticSensor = 4;
int magneticSensorState = LOW;
//int magneticSensorState = LOW;

int solenoidRelay = 5;
int solenoidStatus = LOW;

int ledGreen = 40;
int ledYellow = 42;
int ledRed = 44;

int buzzer = 48;
int buzzerStatus = LOW;

/*
 ************************************************************
 *----------------INITIALIZATION OF DATA--------------------*
 ************************************************************
*/
void setup() {
  
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(pirPin, INPUT);
  pinMode(magneticSensor, INPUT); 
  pinMode(solenoidRelay, OUTPUT);

  Serial.begin(9600);   // Initialize serial communications with the PC

  lcd.begin(16,2);  // Initialize LCD
  lcd.clear();
  lcd.setCursor(1,0);
  lcd.write(2);lcd.write(1);lcd.write(1);
  lcd.print(" SYSTEM ");
  lcd.write(1);lcd.write(1);lcd.write(2);
  lcd.setCursor(2,1);
  lcd.write(2);lcd.write(2);
  lcd.print("  ALERT ");
  lcd.write(2);lcd.write(2);
  
  lcd.createChar(1, heart); // Initializing the Symbol Creation Function in LCD
  lcd.createChar(2, smiley); // Initializing the Symbol Creation Function in LCD
  lcd.createChar(3, frownie); // Initializing the Symbol Creation Function in LCD
  lcd.createChar(4, armsDown); // Initializing the Symbol Creation Function in LCD


  digitalWrite(ledYellow, LOW);
  digitalWrite(ledGreen, HIGH);

/*
 * INITIAL GSM MODULE TESTING
*/

Serial.println("GSM Shield testing. \n");
  //Start configuration of shield with baudrate.
  //For http uses is raccomanded to use 4800 or slower.
  if (gsm.begin(2400)){
    Serial.println("\n Status = READY \n");
    started = true;  
  }
  else Serial.println("\n Status = IDLE \n");
  
  if(started){
    //Enable this two lines if you want to send an SMS.
    if (sms.SendSMS("+254727222982", "INITIAL SMS TESTING.... \n SENT SUCCESSFULLY \n"))
      Serial.println("\n Initial SMS Sent Successfully \n");
      delay(5000);
      (sms.SendSMS("+254727222982", "SYSTEM CONFIGURED SUCCESSFULLY \n"));
      Serial.println("\n Configurations SMS Sent Successfully \n");

      /*
       if(gsm.readSMS(smsbuffer, 160, n, 20))
    {
      Serial.println(n);
      Serial.println(smsbuffer);
    }
    */
  }//END : INITIAL GSM MODULE TESTING

delay(2000);

digitalWrite(ledGreen, HIGH);
digitalWrite(ledYellow, HIGH);

  Sim800l.begin(); // Initializate the library. 
  //Sim800l.reset();
  delay(2000);
  Serial.println("\n SYSTEM RESET SUCCESSFULLY \n");
    //don't forget to catch the return of the function delAllSms! 
  //error = Sim800l.delAllSms(); //clean memory of sms;
  //Sim800l.delAllSms(); //do only if the message is not empty,in other case is not necesary
             //delete all sms..so when receive a new sms always will be in first position
  //delay(5000);

  Serial.println("\n MESSAGES DELETED SUCCESSFULLY \n");
  
  digitalWrite(ledGreen, HIGH);
  digitalWrite(ledYellow, LOW);
  digitalWrite(solenoidRelay, LOW);
  
  delay(2000);
} //END SETUP()

/*
 ************************************************************
 *                                                          *
 *-----------------------MAIN CODE--------------------------*
 *                                                          *
 ************************************************************
*/

void loop(){

  Serial.println("MAIN LOOP CODE EXECUTION");
/*
 * SYSTEM SENDING SMS ALERTS
*/

/*
 * PIR
*/

  pirValue = digitalRead(pirPin);  // read input value

  if (pirValue == HIGH) {            // check if the input is HIGH
    Serial.println("PIR == HIGH");
    
    digitalWrite(ledYellow, HIGH);  // turn YELLOW LED ON
    digitalWrite(ledRed, LOW);
    digitalWrite(ledGreen, LOW);

       lcd.clear();
      lcd.setCursor(0,0); 
      lcd.print("INPUT ACCESS KEY");
      lcd.setCursor(3,1);
      lcd.print(" (-----) ");
  
    delay(1000);
    Serial.println("INPUT ACCESS KEY");

    //keypadCheck();



    String password = "A456#"; // SET Password verification 
    String alfaCode;
    int compareCODE( String alfaCode);    //We type a code on keypad and this will be 
      {                                 //compared with the password;
       if(alfaCode.equals(password))
       return 1; // VALID PASSWORD
       else 
       return 0; // INVALID PASSWORD
       Serial.println("compareCODE");
    } //END compareCODE
    
    char x;
    String takeCode(char x); //Will display on the LCD when the Password is typed
      { char vec[10];
       vec[0] = x;
       lcd.clear();
       lcd.setCursor(3,0);
       lcd.print("PASSWORD:");
       lcd.setCursor(4,0);
       lcd.print('*');
       Serial.println("ENTERING PASSWORD");
       for(int i=1;i<6;i++)
          {
            vec[i] = myKeypad.waitForKey(); //Waits for 5 keys to be pressed and after that  
           lcd.print('*');                  //is taking the decision
           }               
           vec[6]=NULL;
           String str(vec);
           return str;
           Serial.println("waitForKey Processing");
    } //END takeCode
    
      char c = myKeypad.getKey();
    
      if(c != NO_KEY){
        String currentCode = takeCode(c);
        int A = compareCODE(currentCode);
        Serial.println("getKey Processing");
        if(A == 0){         //A is a variable that stores the current code
           lcd.clear();
          lcd.setCursor(0,0);
          lcd.print("INVALID CODE");
          
           delay(2000);
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("ACCESS DENIED");
            
            keypadState = 0;
           return;
           Serial.println("ACCESS DENIED: keypadState 0");
        } //END if (A0)
      
        if(A == 1){
           lcd.clear();
           lcd.setCursor(0,0);
           lcd.print( "VALID CODE " );
            delay(2000);
    
            lcd.clear();
            lcd.setCursor(0,0);
            lcd.print("ACCESS GRANTED");
    
            keypadState = 1;
           return;
      Serial.println("ACCESS GRANTED: keypadState 1");
        } //END if (A1)
       }  // END if NO_KEY

    

    
    delay(5000);
    
    if (pirState == LOW && keypadState == 0) { //WRONG PASSWORD
      // we have just turned on
      
      Serial.println("Motion detected!");
      Serial.println("WRONG PASSWORD");
      
      // We only want to print on the output change, not state
      pirState = HIGH;

      digitalWrite(ledYellow, LOW);
    digitalWrite(ledRed, HIGH);
    digitalWrite(ledGreen, LOW);

    digitalWrite(buzzer, HIGH);
      delay(500);
    Sim800l.sendSms("+254727222982", "Motion Detected \n Wrong Password \n Security Alerts !!!");
    delay(5000);
    }
     if (pirState == LOW && keypadState == 1) { // CORRECT PASSWORD
      // we have just turned on
      
      Serial.println("Motion detected!");
      Serial.println("CORRECT PASSWORD");
      
      // We only want to print on the output change, not state
      pirState = HIGH;

      digitalWrite(ledYellow, LOW);
      digitalWrite(ledRed, LOW);
      digitalWrite(ledGreen, HIGH);

        digitalWrite(solenoidRelay, HIGH);
        
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("(-- WELCOME --)");
      delay(100);
      Sim800l.sendSms("+254727222982", "System Alerts: \n Someone Has Accessed your Premises");
    delay(5000);
    digitalWrite(solenoidRelay, LOW);
    }
  }// END if (pirValue == HIGH) 
  
  else {
    digitalWrite(ledYellow, LOW); // turn YELLOW LED OFF
    
    if (pirState == HIGH){
      // we have just turned off
      
      Serial.println("Motion ended!");
      
      // We only want to print on the output change, not state
      pirState = LOW;
      //Sim800l.sendSms("+254727222982", "No Motion Detected !!!");
    //delay(50000);
    }
  }// END else

/*
 * WINDOW
*/

magneticSensorState = digitalRead(magneticSensor);
  
    if(magneticSensorState == HIGH) 
    {
        //Sim800l.sendSms("+254727222982", "Window is Open");
        if (sms.SendSMS("+254727222982", "Window is Open"))
          Serial.println("WINDOW  IS OPEN");
        }
        else{ //Normally Open : WINDOW IS ALWAYS IN THIS STATE (LOW)
          //Sim800l.sendSms("+254727222982", "Window is Closed");
          if (sms.SendSMS("+254727222982", "Window is Closed"))
            Serial.println("WINDOW IS CLOSED");
          }
          delay(5000);
    //Sim800l.delAllSms();
    //delay(20000);
  
/*
 ****READ SMS***
 *CAPTURE THE SENT SMS AND 
 *EXECUTE IT ACCORDINGLY
*/

textSms=Sim800l.readSms(1); //read the first sms
    
    if (textSms.indexOf("OK")!=-1) //first we need to know if the messege is correct. NOT an ERROR
        {           
        if (textSms.length() > 1)  // optional you can avoid SMS empty
            {
                numberSms=Sim800l.getNumberSms(1);  // Here you have the number
                //for debugging
                Serial.println(numberSms); 
                textSms.toUpperCase();  // set all char to mayus ;)

                if (textSms.indexOf("ALARM")!=-1){
                  alarmStatusFXN();
                  Serial.println("ALARM STATUS");
                }
                else if (textSms.indexOf("ALARMON")!=-1){
                   digitalWrite(buzzer, HIGH); 
                   Serial.println("ALARM ON");
                }
                else if (textSms.indexOf("ALARMOFF")!=-1){
                   digitalWrite(buzzer, LOW); 
                   Serial.println("ALARM OFF");
                }
                else if (textSms.indexOf("PIR")!=-1){
                    pirStatus();
                    Serial.println("PIR STATUS");
                }
                else if (textSms.indexOf("WINDOW")!=-1){
                   windowSensorFXN();
                   Serial.println("WINDOW STATUS");
                }
                else if (textSms.indexOf("DOOR")!=-1){
                   doorStatusFXN(); 
                   Serial.println("DOOR STATUS");
                }
                else if (textSms.indexOf("DOORLOCK")!=-1){
                   digitalWrite(solenoidRelay, LOW);
                   Serial.println("DOOR LOCK");
                }
                else if (textSms.indexOf("DOORUNLOCK")!=-1){
                   digitalWrite(solenoidRelay, HIGH);
                   Serial.println("DOOR UNLOCK");
                }
                else if (textSms.indexOf("STATUS")!=-1){
                   systemStatusFXN(); 
                   Serial.println("GENERAL STATUS");
                }
                else{
                    Serial.println("UNCOMPATIBLE SMS CODE RECIEVED ... :D");
                    Sim800l.sendSms("+254727222982", "UNCOMPATIBLE SMS CODE RECIEVED ... :D");
                     delay(5000);
                }
                
            //Sim800l.delAllSms(); //do only if the message is not empty,in other case is not necesary
             //delete all sms..so when receive a new sms always will be in first position
            }// END (textSms.length() > 1)
        }// END if (textSms.indexOf("OK")!=-1)

        delay(200);
        generalState();
        delay(200);

}//END VOID LOOP()

/*
 ************************************************************
 *                                                          *
 **********************CUSTOM FUNCTIONS**********************
 *                                                          *
 ************************************************************
*
------------------------------------------------------------------------------------------
------------------------------------------------------------------------------------------

/*
 ************************************************************
 *----------------- ALARM STATUS FUNCTION ------------------*
 ************************************************************
*/

void alarmStatusFXN(){
   buzzerStatus = digitalRead(buzzer);

      if (buzzerStatus == HIGH)
      {
        Sim800l.sendSms("+254727222982", " Alarm is ON !! "); // S
      }
      else{
        Sim800l.sendSms("+254727222982", " Alarm is OFF !! ");
      }
      delay(5000);
    //Sim800l.delAllSms();
   // delay(30000);
} // END readAlarmSMS()

/*
 ************************************************************
 *-----------------  PIR STATUS FUNCTION  ------------------*
 ************************************************************
*/    
void pirStatus()
{
    if (pirValue == HIGH) // check if the input is HIGH
    {            
      if (pirState == LOW) {
      // we have just turned on
      Serial.println("Motion detected!");
      // We only want to print on the output change, not state
      Sim800l.sendSms("+254727222982", "Motion Detected \n Security Alerts !!!");
    delay(5000);
    
      pirState = HIGH;

      delay(100);
    }
  }// END if (pirValue == HIGH) 
  else {
    digitalWrite(ledRed, LOW); // turn RED LED OFF
    
    if (pirState == HIGH){
      // we have just turned off
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      Sim800l.sendSms("+254727222982", "No Motion Detected !!!");
        delay(5000);
      pirState = LOW;
    }
  }// END else
} // END pirStatus()

/*
 ************************************************************
 *----------------WINDOW SENSOR FUNCTION------------------*
 ************************************************************
*/

void windowSensorFXN()
{
  
    if(magneticSensorState == LOW) //Normally Open
    {
        Sim800l.sendSms("+254727222982", "Window is Closed");
        }else{
          Sim800l.sendSms("+254727222982", "Window is Open");
          }
          delay(5000);
    //Sim800l.delAllSms();
    //delay(5000);
}// END windowSensor()

/*
 ************************************************************
 *-----------------  DOOR STATUS FUNCTION  ------------------*
 ************************************************************
*/    
void doorStatusFXN()
{
   solenoidStatus = digitalRead(solenoidRelay);
      if (solenoidStatus == LOW)
      {
        Sim800l.sendSms("+254727222982", " Door Locked !! ");
      }
      else{
        Sim800l.sendSms("+254727222982", " Door Openned !! ");
      }
      delay(5000);
    //Sim800l.delAllSms();
    //delay(5000);
} // END doorStatusFXN()
/*
 ************************************************************
 *-----------------  SYSTEM STATUS FUNCTION  ------------------*
 ************************************************************
*/    
void systemStatusFXN()
{
      if (magneticSensorState == LOW && solenoidStatus == HIGH && buzzerStatus == LOW && pirValue == LOW)
      {
        Sim800l.sendSms("+254727222982", " System Secure ");
      }
      if (magneticSensorState == HIGH || solenoidStatus == LOW || buzzerStatus == HIGH || pirValue == HIGH)
      {
        Sim800l.sendSms("+254727222982", " System Insecure ");
      }
      delay(5000);
    //Sim800l.delAllSms();
    //delay(5000);
} // END systemStatusFXN()

void generalState() 
{
  digitalWrite(ledGreen, HIGH);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.write(1);lcd.write(1);lcd.write(2); 
  lcd.print("  SYSTEM  ");
  lcd.write(2);lcd.write(1);lcd.write(1); 
  lcd.setCursor(0,1);
  lcd.write(2);
  lcd.print("  MONITORING  ");
  lcd.write(2);
  } //END GENERAL STATE ()

