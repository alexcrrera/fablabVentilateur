



void globalTemperature(){

  float w = 0.1;

  temperatureGlobal = w * capteur1.temperature + (1-w)*temperatureGlobal;
}