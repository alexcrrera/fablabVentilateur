#include <SPI.h>
#include <SD.h>

#include <EEPROM.h>

const int numFloats = 4;
float randomFloats[numFloats];

File dataFile;
File paraFile;
const int chipSelect = 4; // Chip select pin for the SD card
        // Number of variables to manage
float donneesSD[] = {30,3};       // Array to store the parsed donneesSD


const int sdN =2;//(sizeof(donneesSD) / (donneesSD[0]));
const int eepromStartAddress = 10;

// const char *filenameDonnees = "donneesOut.csv"; // Nom du fichier à vérifier



const int N = 5;//round(sizeof(donneesSD) / (donneesSD[0])); // Taille du tableau

float parameters[N];


  const char *filenamePara = "parametresSysteme.csv"; // Nom du fichier à vérifier


#include <DHT.h>
//#include <LiquidCrystal_I2C.h>

// GLOBAL VAR
#include <Adafruit_SHT31.h>
#include <Adafruit_MLX90614.h>
Adafruit_SHT31 sht31 = Adafruit_SHT31();
#define I2C_ADDR 0x3E

#define LCD_ROWS 2
#define LCD_COLS 16

#include <Wire.h>
#include "rgb_lcd.h"

rgb_lcd lcd;

bool buttonEncoder = false;
bool previousStateButtonEncoder = false;
const int pinButtonEncoder = 5;


#define CAPT1PIN 6
#define CAPT2PIN 3
#define CAPT3PIN 6
#define DHTTYPE1 DHT22 
#define DHTTYPE2 DHT21  
#define DHTTYPE3 DHT21  
DHT dht1(CAPT1PIN, DHTTYPE1);
DHT dht2(CAPT2PIN, DHTTYPE2);
DHT dht3(CAPT3PIN, DHTTYPE3);
const int clkPin = 3;    // CLK pin (connect to Arduino pin 2)
const int dtPin = 2;     // DT pin (connect to Arduino pin 3)









const int signeEncoder = -1;
const int NCAPTEURS = 3;
int capteurCurseur = 0;
//const int pinButton1 = 7;

 int configCurseur = 0;
 const int TAILLECONFIG = 3;
//const int pinButton2 = 7;


float TdesDefault = 30;
float TdesEps = 15; 




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



float stepTemperatureConfig = 0.5;
float stepEpsConfig = 0.1;

float minTemperatureConfig = 10;
float maxTemperatureConfig = 99;

float minEpsConfig = 0.5;
float maxEpsConfig = 9.5;




int lastClkState;
int encoderPosition = 0;
long encoderPos = 0;     // Variable to keep track of the encoder position
bool buttonState = false; // To store button press state


float tabTemperature[NCAPTEURS];

const int UPDATEDATAFREQUENCY = 30;
const int pinSlider1 = A0;
const int POTENTIOMETERFREQUENCY = 5000;
const int SLIDERFREQUENCY = 10;
const int BUTTON1FREQUENCY = 5;
const int LCDFREQUENCY = 2;
const int TEMPERATUREFREQUENCY = 2; // in Hz
int PRINTFREQUENCY = 10; // en Hz

float CAPTEURCURSORFREQUENCY = 1/1.5;

//LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLS, LCD_ROWS);

bool PLOTMODE = false;


float TEMPERATUREHIGHPOINT = 100;
float TEMPERATURELOWPOINT = 0;



const int fan1Pin = 7;
const int fan2Pin = 8;
const int fan3Pin = 9;

float temperatureGlobal = 20; // moyenne valeur - set point pour moyenneur


float EpsdesEps = 5;
const float epsConfigMin = 0.5;
struct sys
{
  float targetTemperature;
  float epsTemperature;
  bool statusTemperature;
  bool button1High;

  //...
};

typedef sys System;

System mainSystem = {20,2.5,false,false};



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

