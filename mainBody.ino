

void setup(){
  
  Serial.begin(115200);
pinMode(53, OUTPUT);
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
  pinMode(fan1Pin,OUTPUT);
//pinMode(A5,INPUT);
pinMode(fan2Pin,OUTPUT);
  dht1.begin();
  dht2.begin();

  lcd.setCursor(0, 0);  // Set cursor to first column of first row
  lcd.print("Initialisation...");
  delay(1000);
  lcd.clear();
  initSD();
  Serial.println("SD init succes !!");
}


void loop(){
  handleCursorCapteur();
  handleButton1();

  handleCommands();

  handleTemperature(); // visiblement cette fonction est en conflit avec la cart SD pour une raison que j'ignore ma théorie est que les librairies des capteurs sont en conflit avec celle de la carte SD...
  handleSlider();
  handleSystemCheck();
  handleFans();
  handlePrint();
  handleLCD();
  handleUpdateData();
  handlePotentiometer();
   handleLogBook();
}