

void setup(){
  
  Serial.begin(115200);
  Serial.println("testW");
  delay(100);
  sht31.begin(0x45);
  lcd.begin(LCD_COLS, LCD_ROWS);
  Serial.println("asdasd");
  //pinMode(pinButton2,INPUT);
  pinMode(clkPin, INPUT);
  pinMode(dtPin, INPUT);
  pinMode(swPin, INPUT_PULLUP); // Use internal pull-up resistor for the button
  lcd.createChar(0, degree); 
  lcd.createChar(1, pminus); 
  Serial.println("akallala");
// pinMode(pinButton1,INPUT);
  pinMode(pinButtonEncoder,INPUT);
  // Read the initial state of CLK
   lastClkState = digitalRead(clkPin);
   //lcd.backlight();
  //Wire.begin();
    Serial.println(F("DEBUT ASDASDASDASD"));
  pinMode(fan1Pin,OUTPUT);
//pinMode(A5,INPUT);
pinMode(fan2Pin,OUTPUT);
  dht1.begin();
  dht2.begin();
  dht3.begin();

  lcd.setCursor(0, 0);  // Set cursor to first column of first row
  lcd.print("Initialisation...");
   delay(1000);
  lcd.clear();










  if (!SD.begin(chipSelect)) {
      Serial.println("SD card initialization failed!"); // pas de carte SD - STOP COMPLET
      lcd.setCursor(0, 0);  // Set cursor to first column of first row
      lcd.print("SD PAS DETECTEE!!");
      delay(1000);
      //while (true); // Halt execution
  }


  Serial.println("SD card initialized.");
/*
  // Load data from SD card, or create file if it doesn't exist
  if (!loadDataFromSD("parametresSysteme.csv")) {
    Serial.println("File not found. Creating a new one...");
    lcd.setCursor(0, 0);  // Set cursor to first column of first row
      lcd.print("CONFIGURER SYS");
      delay(1000);
  
/*
    if (!createDefaultFile("parametresSysteme.csv")) {
      Serial.println("Error creating the default file.");
      lcd.setCursor(0, 0);  
      lcd.print("ERREUR TERMINALE"); // RIP
      while(true);
    }
    
  }

  */
Serial.println("12132413431414 hajjaja");
    lcd.setCursor(0, 0);  // Set cursor to first column of first row
  lcd.print("SYS CHECK GOOD ");
  delay(2000);
  
  lcd.clear();
  delay(500);

  Serial.println("starting lcdsstw");



  //initSystem(); Startup du logiciel

    Serial.println("starting lcdasdasdasdivjmsarvvnisstw");

}


void loop(){
  handleCursorCapteur();
  handleButton1();
  handleCommands();
  handleTemperature();

  handleSlider();
  handleSystemCheck();
  handleFans();
  handlePrint();
  handleLCD();
 handleUpdateData();
  handlePotentiometer();
}