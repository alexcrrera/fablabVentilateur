#include <SPI.h>
#include <SD.h>
#include <EEPROM.h>
#include <DHT.h>
#include <Adafruit_SHT31.h>
#include <Adafruit_MLX90614.h>
#include <Wire.h>
#include "rgb_lcd.h"



int counterAddress = 0;
int logCounter = 0;
bool BYPASSSD = false; //  pour tester code sans module SD


Sd2Card card;

const int chipSelect = 53;   // Chip select pin for the SD card


const int sdN =2;           // amount of data we want to store in EEPROM (so the heating settings)
const int eepromStartAddress = 10;
float EEPROMDATA[sdN+1];  //array of data to store the parameters to save to EEPROM

 char fileName[15];

Adafruit_SHT31 sht31 = Adafruit_SHT31();
#define I2C_ADDR 0x3E

#define LCD_ROWS 2
#define LCD_COLS 16



rgb_lcd lcd;



#define CAPT1PIN 7
#define CAPT2PIN 8
#define DHTTYPE1 DHT22 
#define DHTTYPE2 DHT21   
DHT dht1(CAPT1PIN, DHTTYPE1);
DHT dht2(CAPT2PIN, DHTTYPE2);



const int clkPin = A4;    // CLK pin (connect to Arduino pin 2)
const int dtPin = A5;     // DT pin (connect to Arduino pin 3)
bool buttonEncoder = false;
bool previousStateButtonEncoder = false;
const int pinButtonEncoder = 9;




const int signeEncoder = -1;
const int NCAPTEURS = 3;   // nombre de capteurs
int capteurCurseur = 0;

int configCurseur = 0;
const int TAILLECONFIG = 3;




byte degree[8] = {
  B00010,  // Empty row
  B00101,  // Dot (top part)
  B00010,  // Dot (middle part)
  B00000,  // Empty row
  B00000,  // Dot (bottom part)
  B00000   // Empty row
};



byte pminus[8] = {
  B00000,  // Empty row
  B00000,  // Dot (top part)
  B00100,  // Dot (middle part)
  B01110,  // Empty row
  B00100,  // Dot (bottom part)
   B00000,  // Empty row
  B01110,  // Empty row
   B00000,  // Empty row
};

byte circ[8] = {
  B01000,  // Empty row
  B10100,  // Dot (top part)
  B01000,  // Dot (middle part)
  B00000,  // Empty row
  B00000,  // Dot (bottom part)
  B00000   // Empty row
};



const float stepTemperatureConfig = 0.5;
const float stepEpsConfig = 0.1;

const float minTemperatureConfig = 10;
const float maxTemperatureConfig = 50;

const float minEpsConfig = 0.5;
const float maxEpsConfig = 9.5;




int lastClkState;
int encoderPosition = 0;
long encoderPos = 0;     // Variable to keep track of the encoder position


float tabTemperature[NCAPTEURS];
float tabHumidite[NCAPTEURS];

const int UPDATEDATAFREQUENCY = 30;
const int POTENTIOMETERFREQUENCY = 5000;
const int SLIDERFREQUENCY = 10;
const int BUTTON1FREQUENCY = 5;
const int LCDFREQUENCY = 2;
const int TEMPERATUREFREQUENCY = 2; // in Hz
const int PRINTFREQUENCY = 10; // en Hz
const float CAPTEURCURSORFREQUENCY = 1/1.5;
const float SDDATALOGFREQUENCY = 0.06; // en Hz


bool PLOTMODE = false;


float TEMPERATUREHIGHPOINT = 100;
float TEMPERATURELOWPOINT = 0;



const int fan1Pin = 12;
const int fan2Pin = 13;
const int fan3Pin = 10;
//const int fan4Pin = 11; n est pas utilise pour l'instant


float temperatureGlobal = 20; // moyenne valeur - set point pour moyenneur


struct sys
{
  float targetTemperature;
  float epsTemperature;

  //...
};

typedef sys System;

System mainSystem;


struct capteur
{
  float temperature;
  float humidite;
  bool hysteresisStatusHigh;
  bool fanOn;
  bool flag;
};

typedef capteur Capteur;

Capteur capteur1 = {0,0,false,false,false};

Capteur capteur2 = {0,0,false,false,false};

Capteur capteur3 = {0,0,false,false,false};

