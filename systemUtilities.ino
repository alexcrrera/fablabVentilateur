void handleSystemCheck(){
 // bool checkInter = checkTemperatureSurpassed();
 // mainSystem.statusTemperature = checkInter;
  capteur1.fanOn = checkTemperatureSurpassedCapteur1();
   capteur2.fanOn = checkTemperatureSurpassedCapteur2();
    capteur3.fanOn = checkTemperatureSurpassedCapteur3();
 
  
      
    
}
unsigned long timeButton1 = 0;

void handleButton1(){

    if((millis()-timeButton1)*1.0>=1000.0/BUTTON1FREQUENCY){
    timeButton1 = millis();
   checkButton1();
    
  }


}
void handleFans(){

  digitalWrite(fan1Pin,capteur1.fanOn);
  digitalWrite(fan2Pin,capteur2.fanOn);
   digitalWrite(fan3Pin,capteur3.fanOn);
 
}
unsigned long timeLCD = 0;

void handleLCD(){ // donnees a certains Hz
  
  if((millis()-timeLCD)*1.0>=1000.0/LCDFREQUENCY){
    timeLCD = millis();
   printLCD();
    
  }

}

void printLCD(){
  

  partUpperLCD();
  partLowerLCD();



  return;
}



void partUpperLCD(){
  lcd.setCursor(6,0);
  lcd.print("                ");
  lcd.setCursor(0,0);
  lcd.print("CAPT ");
 
  lcd.print(capteurCurseur+1);
  lcd.print(": ");
  
  lcd.print(tabTemperature[capteurCurseur],1);
  lcd.write(byte(0));
  lcd.print("C");
// flags
  switch(capteurCurseur){
    case 0: // capteur 1
     if(capteur1.flag){
         lcd.setCursor(LCD_COLS-1,0);
         lcd.print("!!");
  }
  else{
      lcd.setCursor(LCD_COLS-1,0);
        lcd.print("  ");
  }
  break;

    case 1: // capteur 1
     if(capteur2.flag){
         lcd.setCursor(LCD_COLS-1,0);
         lcd.print("!!");
  }
  else{
      lcd.setCursor(LCD_COLS-1,0);
        lcd.print("  ");
  }
  break;

    case 2: // capteur 1
     if(capteur3.flag){
         lcd.setCursor(LCD_COLS-1,0);
         lcd.print("!!");
  }
  else{
      lcd.setCursor(LCD_COLS-1,0);
        lcd.print("  ");
  }
  break;



  }
 
  //lcd.setCursor(0,4);

}

void partLowerLCD(){
   /*
   lcd.setCursor(0,2);

   lcd.print("CONF TEMP: ");
   lcd.print(mainSystem.targetTemperature,1);
  lcd.write(byte(0));
  lcd.print("C");
    lcd.setCursor(0,3);
   lcd.print("CONF EPS:  ");
   lcd.write(byte(1));
   lcd.print(mainSystem.epsTemperature,1);
  lcd.write(byte(0));
  lcd.print("C");
  */
}


unsigned long timePotentiometer;


void handlePotentiometer(){ // donnees a certains Hz
  
  if((millis()-timePotentiometer)*1.0>=1000.0/POTENTIOMETERFREQUENCY){
    timePotentiometer = millis();
  checkPotentiometer();
  }

}


void updateCurseurConfig(){
  configCurseur++;
    encoderPosition = 0;
    if(configCurseur > TAILLECONFIG-1){
      configCurseur = 0;
    }
}

void updateCurseurCapteur(){
    capteurCurseur++;
    if(capteurCurseur > NCAPTEURS-1){
      capteurCurseur = 0;
    }
}

void checkButton1(){

   if(!digitalRead(pinButtonEncoder)){
  //if(digitalRead(pinButton2) || !digitalRead(pinButtonEncoder)){
    //mainSystem.button1High = mainSystem.button1High;
    updateCurseurConfig();
  }
  
}

unsigned long timeSlider = 0;;


void handleSlider(){
    if((millis()-timeSlider)*1.0>=1000.0/SLIDERFREQUENCY){
    timeSlider = millis();
  //checkPotentiometer();

  checkSlider();
  }
}




unsigned long timeCursorCapteur = 0;;


void handleCursorCapteur(){
    if((millis()-timeCursorCapteur)*1.0>=1000.0/CAPTEURCURSORFREQUENCY){
    timeCursorCapteur = millis();
  //checkPotentiometer();

  updateCurseurCapteur();
  }
}




void checkSlider(){

    lcd.setCursor(LCD_COLS-1,2);
    lcd.print("<");
    lcd.setCursor(LCD_COLS-1,3);
    lcd.print(" ");
  // lcd.setCursor(17,2);
  // lcd.print("               ");
 
  switch(configCurseur){




    case 0: // temp des
     lcd.setCursor(7,2);
     lcd.print("       ");
    lcd.setCursor(0,2);
    lcd.print("TDES: ");
    lcd.print(mainSystem.targetTemperature,1);
    lcd.write(byte(0));
    lcd.print("C");
    
    
    
    
    
    lcd.setCursor(LCD_COLS-1,3);
   lcd.print(" ");
    lcd.setCursor(LCD_COLS-1,2);
     lcd.print("<");
   break;



  case 1: // EPS DES
   lcd.setCursor(7,2);
     lcd.print("       ");
    lcd.setCursor(0,2);
   lcd.print("DEPS:  ");
   lcd.write(byte(1));
   lcd.print(mainSystem.epsTemperature,1);
  lcd.write(byte(0));
  lcd.print("C");
  lcd.setCursor(LCD_COLS-1,2);
  lcd.print(" ");
    lcd.setCursor(LCD_COLS-1,3);
  lcd.print("<");
  //lcd.setCursor(17,3);
   //lcd.print("               ");



  break;

  case 2:
capteur1.hysteresisStatusHigh = false;
capteur2.hysteresisStatusHigh = false;
capteur3.hysteresisStatusHigh = false;
 lcd.setCursor(LCD_COLS-1,2);
  lcd.print(" ");
   lcd.setCursor(LCD_COLS-1,3);
  lcd.print(" ");
  configCurseur = 0;
 // Serial.print(" Done config");
  default:
  break;
  }

  

}




void checkPotentiometer(){
   
 int currentClkState = digitalRead(clkPin);
  
  // Check for a change in the CLK state (encoder rotated)
  if (currentClkState != lastClkState) {
    // Determine the direction based on the state of DT
    if (digitalRead(dtPin) != currentClkState) {
      encoderPosition = -1*signeEncoder;
    } else {
      encoderPosition = 1*signeEncoder;
    }
    
    // Print the encoder position
 //   Serial.print("Encoder Position: ");
   // Serial.println(encoderPosition);
  }
 
  // Update the last state of CLK
  lastClkState = currentClkState;
  
  // Check the state of the button
  bool buttonState = digitalRead(pinButtonEncoder) == LOW; // LOW means pressed
  
  // Print the button state
 // Serial.print("Button State: ");

  
  // Add a small delay to avoid flooding the Serial Monitor



}



unsigned long timeDataUpdate;


void handleUpdateData(){ // donnees a certains Hz
  
  if((millis()-timeDataUpdate)*1.0>=1000.0/UPDATEDATAFREQUENCY){
    timeDataUpdate = millis();
  updateTemperature();
  }

}

void updateTemperature(){
    switch(configCurseur){
      case 0:

        mainSystem.targetTemperature += encoderPosition*stepTemperatureConfig;
        encoderPosition = 0;
        if(mainSystem.targetTemperature >=maxTemperatureConfig){
          mainSystem.targetTemperature =maxTemperatureConfig;
          }
        if(mainSystem.targetTemperature <=minTemperatureConfig){
          mainSystem.targetTemperature =minTemperatureConfig;
        }

      break;

      case 1:
        mainSystem.epsTemperature += encoderPosition*stepEpsConfig;
        encoderPosition = 0;

      if(mainSystem.epsTemperature >=maxEpsConfig){
        mainSystem.epsTemperature =maxEpsConfig;
      }
      if(mainSystem.epsTemperature <=minEpsConfig){
        mainSystem.epsTemperature = minEpsConfig;
      }
      break;

    }
}
