


bool checkTemperatureSurpassedCapteur1(){
  if(capteur1.hysteresisStatusHigh == false && capteur1.temperature  >= TEMPERATUREHIGHPOINT){
    capteur1.hysteresisStatusHigh = true;
    return(true);
  }

  if(capteur1.hysteresisStatusHigh && capteur1.temperature >= TEMPERATURELOWPOINT){
    return(true);
  }
 capteur1.hysteresisStatusHigh = false;
    return(false);
  }





bool checkTemperatureSurpassedCapteur2(){
  if(capteur2.hysteresisStatusHigh == false && capteur2.temperature  >= TEMPERATUREHIGHPOINT){
    capteur2.hysteresisStatusHigh = true;
    return(true);
  }

  if(capteur2.hysteresisStatusHigh && capteur2.temperature >= TEMPERATURELOWPOINT){
    return(true);
  }
 capteur2.hysteresisStatusHigh = false;
    return(false);
  }



bool checkTemperatureSurpassedCapteur3(){
  if(capteur3.hysteresisStatusHigh == false && capteur3.temperature >= TEMPERATUREHIGHPOINT){
    capteur3.hysteresisStatusHigh = true;
    return(true);
  }

  if(capteur3.hysteresisStatusHigh && capteur3.temperature >= TEMPERATURELOWPOINT){
    return(true);
  }
 capteur3.hysteresisStatusHigh = false;
    return(false);
  }








void configSetPointsTemp(){

 TEMPERATUREHIGHPOINT = mainSystem.targetTemperature + mainSystem.epsTemperature;
 
  TEMPERATURELOWPOINT = mainSystem.targetTemperature -mainSystem.epsTemperature;


}

