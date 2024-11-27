unsigned long timePrint = 0;


void handleCommands(){

  if(Serial.available()){
  
 byte incomingByte = Serial.read();
  if(incomingByte == 'P'){
    PLOTMODE = !PLOTMODE;
    Serial.println("MODE DE PLOT CHANGE");
  }

  }
}





void handlePrint(){ //
  
  if((micros()-timePrint)*1.0>=1000.0*1000/PRINTFREQUENCY){
    timePrint = micros();
    getPrint(); 
  }
}

void printSingle(String header, float d1){

  String res = " " + header + ": ";

  if(PLOTMODE){
    res = "";
  }
  Serial.print(res  + String(d1)+",");
}

void printGroup(String header, float d1, float d2, float d3){

  String res = header + ": ";

  if(PLOTMODE){
    res = "";
  }
  Serial.print(res  + String(d1) + "," + String(d2) + ","+ String(d3)+",");
}




void getPrint() {

 
  Serial.print("\n");
  printSingle("Temperature glob",temperatureGlobal);
  //printSingle("Temperature i", capteur1.temperature);
  printGroup("Temperature",capteur1.temperature,capteur2.temperature,capteur3.temperature);
  printGroup("Ventilateurs",capteur1.fanOn,capteur2.fanOn,capteur3.fanOn);
  //int f1 =  mainSystem.fan1On == true ? 1 : 0;
   // int f2 =  mainSystem.fan2On == true ? 1 : 0;
  //printSingle("fan 1",capteur1.fanOn);
   //printSingle("fan 2",capteur2.fanOn);

   printSingle("Temperature Desiree",mainSystem.targetTemperature);

   //printSingle("high: ",TEMPERATUREHIGHPOINT);
     // printSingle("low: ",TEMPERATURELOWPOINT);

    printSingle("Menu",configCurseur);
//printSingle("STATE ENCODER",previo;usStateButtonEncoder);
   // printSingle("Button",  capteurCurseur);
   // printSingle("r",digitalRead(pinButtonEncoder));

    //printSingle("Rot",encoderPosition);
  
  //printSingle("Upper lim", 30);
  //printSingle("Upper lim", 18);
  
  }

