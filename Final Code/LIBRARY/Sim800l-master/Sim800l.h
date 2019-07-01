/* This library was originally written by  Cristian Steib.
 *      steibkhriz@gmail.com
 *	EDITED BY Kithinji A. Muriungi
 *		(+)254-718 605 065
		Electrical & Electronics Engineering Student 
			Moi University, Kenya.
 *  Designed to work with the GSM Sim800l,maybe work with SIM900L
 *  
 *     This library use SoftwareSerial, you can define RX and TX pin
 *     in the header "Sim800l.h" ,by default the pin is RX=10 TX=11..
 *     be sure that gnd is attached to arduino too. 
 *     You can also change the other preferred RESET_PIN
 *    
 *   
 *     
 *    PINOUT: 
 *        _____________________________
 *       |  ARDUINO UNO >>>   SIM800L  |
 *        -----------------------------
 *            GND      >>>   GND
 *        RX  8       >>>   TX  
 *        TX  9       >>>   RX
 *       RESET 2       >>>   RST 
 *                 
 *   POWER SOURCE 4.2V >>> VCC
 *
 *    Edited on: September 9, 2017
 *        
 *
*/
#ifndef Sim800l_h
#define Sim800l_h
#include <SoftwareSerial.h>
#include "Arduino.h"


#define RX_PIN 10	//TX pin on the SIM800L
#define TX_PIN 11	//RX pin on the SIM800L
#define RESET_PIN 2  // pin to the reset pin sim800l

#define LED true // used for indicator led, in case that you don want set to false . 
#define LED_PIN 13 //pin to indicate states. 




class Sim800l		
{									
  private:
	int _timeout;
	String _buffer;
		String _readSerial();
  	
  	
  public:

 	void begin();	
 	void reset(); 

 	// Methods for calling
 	bool answerCall(); 	
 	void callNumber(char* number);
 	bool hangoffCall();
 	uint8_t getCallStatus();   
 	//Methods for sms 
	bool sendSms(char* number,char* text);	 
	String readSms(uint8_t index); //return all the content of sms
	String getNumberSms(uint8_t index); //return the number of the SMS   
	bool delAllSms();     // return :  OK or ERROR 

	void signalQuality();
	void setPhoneFunctionality();
	void activateBearerProfile();
	void deactivateBearerProfile();
	//get time with the variables by reference
	void RTCtime(int *day,int *month, int *year,int *hour,int *minute, int *second);  
	String dateNet(); //return date,time, of the network
	bool updateRtc(int utc);  //Update the RTC Clock with de Time AND Date of red-.
};

#endif 