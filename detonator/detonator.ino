//-----------------------------------------------------------------------
// DETONATOR
// Code to be run by the YUAA detonator for purposes of blasting three
// igniters in the upper section of the Omega rocket.
//
// Author: Jan Kolmas (jan.kolmas@gmail.com)
// Last edit: 4/24/2014
//----------------------------------------------------------------------- 
// Inputs:  4 switches
//          Radio commands
// Outputs: 6 LEDs
//          Radio commands
//----------------------------------------------------------------------

// Switch inputs
boolean arm = false;
boolean chute = false;
boolean fairing = false;
boolean deploy = false;

// State variables
boolean armed = false;
boolean chute_on = false;
boolean fairing_on = false;
boolean deploy_on = false;

// Timers
int last = millis();

void setup(){
  
  // Configure switches as inputs
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(4,INPUT);
  pinMode(5,INPUT);
  
  // Configure LEDs as outputs
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(7,OUTPUT);
  
  // Activate pullup resistors on inputs
  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
  digitalWrite(4,HIGH);
  digitalWrite(5,HIGH);
  
  // Turn the red power LED on
  digitalWrite(8,HIGH);
  
  // Open serial communication
  Serial.begin(9600);
}

void loop(){
  
  // Read state of the switches
  arm = !digitalRead(2);
  chute = !digitalRead(3);
  fairing = !digitalRead(4);
  deploy = !digitalRead(5);
  
  // Read data from the radio if any
  String serialData = getSerialData();
  
  // Send the ARM command, blink the LED  
   if(arm&&!armed){
       Serial.println("ARM");
       digitalWrite(9,HIGH);
       delay(50);
       digitalWrite(9,LOW);
       delay(50);     
       armed = true;
   }
   
   // Send the DRM command, blink the LED
   else if(!arm&&armed){
       Serial.println("DRM");
       digitalWrite(9,HIGH);
       delay(50);
       digitalWrite(9,LOW);
       delay(50);     
       armed = false;
   }
   
   // Send the CHT command, blink the LED
   if(chute&&armed&&!chute_on){
       chute_on = true;
       Serial.println("CHT");
       digitalWrite(10,HIGH);
       delay(50);
       digitalWrite(10,LOW);
       delay(50);
       
  }
  else if(!chute&&chute_on){ // switch was flipped down
      chute_on = false;
  }
  else{
    digitalWrite(10,LOW); 
  }
  
 // Send the FRG command, blink the LED
  if(fairing&&armed&&!fairing_on){
       fairing_on = true;
       Serial.println("FRG");
       digitalWrite(11,HIGH);
       delay(50);
       digitalWrite(11,LOW);
       delay(50);
       
  }
  else if(!fairing&&fairing_on){ // switch was flipped down
      fairing_on = false;
  }
  else{
    digitalWrite(11,LOW); 
  }
  
  // Send the DPL command, blink the LED
  if(deploy&&armed&&!deploy_on){
      deploy_on = true;
       Serial.println("DPL");
       digitalWrite(12,HIGH);
       delay(50);
       digitalWrite(12,LOW);
       delay(50);
       
  }
  else if(!deploy&&deploy_on){ // switch was flipped down
      deploy_on = false;
  }
  else{
    digitalWrite(12,LOW); 
  }
      
  // If the e-bay responds with ACK, blink the white LED    
  if(serialData.equals("ACK\r")){
    digitalWrite(7,HIGH);
    delay(50);
    digitalWrite(7,LOW);
    delay(50);
  
  }
  else{
    digitalWrite(7,LOW); 
  }
 
  
}


// Function for reading Serial commands
String getSerialData(){
   String serialData = "";
   char inbyte; 
  // Read serial data as long as its available.  
   while(Serial.available()) {
     inbyte = Serial.read();
     if(inbyte != '\n') serialData.concat(inbyte);
     delay(10);
   }   
   if(serialData != "") {
     //Serial.println(serialData);
     return serialData;
   }   
}


