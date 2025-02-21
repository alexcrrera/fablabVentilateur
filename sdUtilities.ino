
int getAndIncrementCounter() {
  int counter = EEPROM.read(counterAddress); // Read counter from EEPROM
  counter++;                                // Increment counter
  EEPROM.update(counterAddress, counter);   // Write updated counter to EEPROM
  return counter;
}




void initSD(){
retrieveFloatsFromEEPROM();

mainSystem.epsTemperature = EEPROMDATA[1];
mainSystem.targetTemperature = EEPROMDATA[0];

Serial.println(mainSystem.epsTemperature);

Serial.println(mainSystem.targetTemperature);

Serial.println("starting SD init");


if (!SD.begin(chipSelect) && !BYPASSSD) {
  

 

  Serial.println("SD card initialization failed!"); // pas de carte SD - STOP COMPLET
  lcd.setCursor(0, 0);  // Set cursor to first column of first row
  lcd.print("SD PAS DETECTEE!");
  lcd.setCursor(0, 1);  // Set cursor to first column of first row
  lcd.print("ERREUR FATALE!!");
  while (true); // Halt execution
}

if(!BYPASSSD){
   int fileCounter = getAndIncrementCounter();

  // e.g., "log001.csv\0"
    snprintf(fileName, sizeof(fileName), "log%03d.csv", fileCounter); // CREQTION NOM

}

}




void retrieveFloatsFromEEPROM() {
  int address = eepromStartAddress;


  for (int i = 0; i < sdN+1; i++) {
    byte floatBytes[sizeof(float)];
    for (int j = 0; j < sizeof(float); j++) {
      float data = EEPROM.read(address++);
      if(isnan(data)){
        data = 5;
        Serial.println("no data in EEPROM");
      }
      floatBytes[j] = data;
    }
    EEPROMDATA[i] = *((float*)floatBytes);


    counterAddress = sizeof(float)*sdN +1;
    if(isnan(EEPROMDATA[i])){
      EEPROM.update(i, 69);
    }
  }


  
logCounter = round(EEPROMDATA[2]);

Serial.println(EEPROMDATA[0]);
Serial.println(EEPROMDATA[1]);
Serial.print("\n N LOBOOK:");
Serial.println(logCounter);
Serial.println("!!!!!");
    
    delay(2000);
  }




void updateParaData(){
int st = eepromStartAddress;
byte floatBytes[sizeof(float)];
Serial.println("W2mem");
 for (int i = 0; i < sdN; i++) {
    *((float*)floatBytes) = EEPROMDATA[i];
    for (int j = 0; j < sizeof(float); j++) {
      EEPROM.update(st, floatBytes[j]);
      st++;
      
   

    }
  }


}





void LogBook(){
  if(BYPASSSD){
    return;
  }
  Serial.println("attempting to open SD");

  String dataString = "";

  for (int i = 0; i < NCAPTEURS ; i++) {
    dataString += String(tabTemperature[i]);
    dataString += ",";
    dataString += String(tabHumidite[i]);
    if (i < NCAPTEURS-1){
      dataString += ",";
    }
  }

  Serial.println("attempting to open SD");

  File dataFile = SD.open(fileName, FILE_WRITE);

  // if the file is available, write to it:
  if (dataFile) {
    dataFile.println(dataString);
    dataFile.close();
    // print to the serial port too:
    Serial.println(dataString);
  }
  // if the file isn't open, pop up an error:
  else {
    Serial.println("error opening datalog.txt");
  }
}

