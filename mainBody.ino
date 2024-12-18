

void setup(){
  
  Serial.begin(115200);

  sht31.begin(0x45);
  lcd.begin(LCD_COLS, LCD_ROWS);
  Serial.println("INIT");
  //pinMode(pinButton2,INPUT);
  pinMode(clkPin, INPUT);
  pinMode(dtPin, INPUT);
  pinMode(pinButtonEncoder, INPUT_PULLUP); 
  lcd.createChar(0, degree); 
  lcd.createChar(1, pminus); 

// pinMode(pinButton1,INPUT);

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








  initSD();


    lcd.setCursor(0, 0);  // Set cursor to first column of first row
  lcd.print("SYS CHECK GOOD ");

  lcd.clear();
  delay(500);


  //initSystem(); Startup du logiciel


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