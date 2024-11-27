

void setup(){
  
  Serial.begin(115200);
  Serial.println("test");
  delay(100);
  lcd.init();
  pinMode(pinButton2,INPUT);
  pinMode(clkPin, INPUT);
  pinMode(dtPin, INPUT);
  pinMode(swPin, INPUT_PULLUP); // Use internal pull-up resistor for the button
 lcd.createChar(0, degree); 
  lcd.createChar(1, pminus); 
 pinMode(pinButton1,INPUT);
 pinMode(pinButtonEncoder,INPUT);
  // Read the initial state of CLK
   lastClkState = digitalRead(clkPin);
   lcd.backlight();
  //Wire.begin();
  pinMode(fan1Pin,OUTPUT);
//pinMode(A5,INPUT);
pinMode(fan2Pin,OUTPUT);
  dht1.begin();
  dht2.begin();
  dht3.begin();
  Serial.println(F("DEBUT PROGRAMME"));
  lcd.setCursor(0, 0);  // Set cursor to first column of first row
  lcd.print("Initialisation...");
 
  lcd.clear();

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