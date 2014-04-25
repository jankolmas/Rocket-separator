//-----------------------------------------------------------------------
// OMEGA EBAY
// Code to be run by the YUAA Omega e-bay for purposes of blasting three
// igniters in the upper section of the Omega rocket.
//
// Author: Jan Kolmas (jan.kolmas@gmail.com)
// Last edit: 4/24/2014
//----------------------------------------------------------------------- 
// Inputs:  Radio commands
// Outputs: Radio commands
//          1 LED
//-----------------------------------------------------------------------

// State variables
boolean armed = false;
boolean released = false;
boolean blinkstate = false;

// Delays
int timeDelay = 5000;
int longDelay = 1000;

// Pin definitions
int pinChute1 = 2;
int pinFairing1 = 3;
int pinDeploy1 = 4;

// Commands
String arm = "ARM\r";
String disarm = "DRM\r";
String chute = "CHT\r";
String deploy = "DPL\r";
String fairing = "FRG\r";

// Timers
long int timer_chute = millis();
long int timer_fairing = millis();
long int timer_deploy = millis();
long int timer_long = millis();

String serialData = "";

void setup()
{
  // Set igniter pins as outputs
  pinMode(pinChute1, OUTPUT);
  pinMode(pinFairing1, OUTPUT);
  pinMode(pinDeploy1, OUTPUT); 
  
  // Open serial communication
  Serial.begin(9600);
}

void loop()
{
  // Read serial commands if any  
  serialData = getSerialData();
  
  // Arming command received, send acknowledge command
  if(serialData.equals(arm) && !armed){
    armed = true;
    Serial.println("ACK");
  } 
  
  // Disarming command received, send acknowledge command
  else if(serialData.equals(disarm) && armed){
    armed = false;
    blinkstate = false;
    digitalWrite(13, LOW);
    Serial.println("ACK");
  } 
  
  // Command for firing the chute igniter received
  else if(serialData.equals(chute) && armed){
    timer_chute = millis();
  }
  
  // Command for firing the fairing igniter received
  else if(serialData.equals(fairing) && armed){
    timer_fairing = millis();
  }
  
  // Command for firing the UAV deployment igniter received
  else if(serialData.equals(deploy) && armed){
    timer_deploy = millis();
  }
  
  // Keep the chute igniter pin high for the prescribed delay, light the LED
  if(timer_chute > millis()-timeDelay){
    digitalWrite(pinChute1, HIGH);
    digitalWrite(13, HIGH);
  }
  else{
    digitalWrite(pinChute1, LOW);
  }
  
  // Keep the fairing igniter pin high for the prescribed delay, light the LED
  if(timer_fairing > millis()-timeDelay){
    digitalWrite(pinFairing1, HIGH);
    digitalWrite(13, HIGH);
  }
  else{
    digitalWrite(pinFairing1, LOW);
  }
  // Keep the deployment igniter pin high for the prescribed delay, light the LED
  if(timer_deploy > millis()-timeDelay){
    digitalWrite(pinDeploy1, HIGH);
    digitalWrite(13, HIGH);
  }
  else{
    digitalWrite(pinDeploy1, LOW);
  }
  
  // Blink the LED slowly if system is armed  
  if(armed && timer_long+longDelay < millis()){
    timer_long = millis();
    if(blinkstate == false){
      blinkstate = true;
      digitalWrite(13, HIGH);
    }
    else{
      blinkstate = false;
      digitalWrite(13, LOW);
    }
    
  }

 
}


// Function for reading serial data.
String getSerialData()
{
  String data = "";
  char inbyte;
  if(!Serial.available()) return "";
  while(Serial.available()) {
    inbyte = Serial.read();
    if(inbyte != '\n')
      data+=inbyte;
    delay(10);
  }

  if(data != "") {
    //Serial.println(data);
    return data;
  }

}

