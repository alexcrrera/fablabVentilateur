
unsigned long timeTemperature = 0;


void handleTemperature(){ // donnees a certains Hz
  
  if((millis()-timeTemperature)*1.0>=1000.0/TEMPERATUREFREQUENCY){
   
    timeTemperature = millis();
    readSensor1(); readSensor2();readSensor3();
    globalTemperature(); // updates temperature avec filtre
    configSetPointsTemp();
    tabTemperature[0] =  capteur1.temperature;
    tabTemperature[1] =  capteur2.temperature;
    tabTemperature[2] =  capteur3.temperature;
    tabHumidite[0] = capteur1.humidite;
    tabHumidite[1] = capteur2.humidite;
    tabHumidite[2] = capteur3.humidite;
  }

}



void readSensor1(){
  
  float midT = dht1.readTemperature();
  capteur1.temperature = (isnan(midT) ? capteur1.temperature : midT);
  capteur1.flag = (isnan(midT) ? true : false);
   if(isnan(midT)){ Serial.println("erreur reading t1");}

  midT =  dht1.readHumidity();
  capteur1.humidite = (isnan(midT) ?  capteur1.humidite  : midT);
    if(isnan(midT)){ Serial.println("erreur reading h1");}
     capteur1.flag = (isnan(midT) ? true : false);
   
}



void readSensor3(){
  
  float midT = sht31.readTemperature();//dht3.readTemperature();
  capteur3.temperature = (isnan(midT) ? capteur3.temperature : midT);
   capteur3.flag = (isnan(midT) ? true : false);
   

  midT =  sht31.readHumidity();//dht3.readHumidity();
  capteur3.humidite = (isnan(midT) ?  capteur3.humidite  : midT);
 
     capteur3.flag = (isnan(midT) ? true : false);
  
}



void readSensor2(){
  
  float midT = dht2.readTemperature();
  capteur2.temperature = (isnan(midT) ? capteur2.temperature : midT);
  
   if(isnan(midT)){ Serial.println("erreur reading t2");}

  midT =  dht2.readHumidity();
  capteur2.humidite = (isnan(midT) ?  capteur2.humidite  : midT);
    
     capteur2.flag = (isnan(midT) ? true : false);
 
}

