









void initSD(){
//generateRandomFloats();
retrieveFloatsFromEEPROM();

mainSystem.epsTemperature = donneesSD[1];
mainSystem.targetTemperature = donneesSD[0];

Serial.println(mainSystem.epsTemperature);

Serial.println(mainSystem.targetTemperature);
delay(500);
/*
  
  if (!SD.begin(chipSelect)) {
      Serial.println("SD card initialization failed!"); // pas de carte SD - STOP COMPLET
      lcd.setCursor(0, 0);  // Set cursor to first column of first row
      lcd.print("SD PAS DETECTEE!");
       lcd.setCursor(0, 1);  // Set cursor to first column of first row
      lcd.print("ERREUR FATALE!!");
      while (true); // Halt execution
  }

  Serial.println("SD card ok.");
 
  if (SD.exists(filenameDonnees)) {
    Serial.print("Le fichier ");
    Serial.print(filenameDonnees);
    Serial.println(" existe déjà !");
    } else {
    Serial.print("Le fichier ");
    Serial.print(filenameDonnees);
    Serial.println(" n'existe pas. Création du fichier...");

    File file = SD.open(filenameDonnees, FILE_WRITE);
    if (file) {
  
      Serial.println("Fichier créé avec succès !");
    } else {
      Serial.println("Échec de la création du fichier !");
    }
  }

  if (SD.exists(filenamePara)) {
    Serial.print("Le fichier ");
    Serial.print(filenamePara);
    Serial.println(" existe déjà !");
    } else {
    Serial.print("Le fichier ");
    Serial.print(filenamePara);
    Serial.println(" n'existe pas. Création du fichier...");

    File file = SD.open(filenamePara, FILE_WRITE);
    if (file) {
  
      Serial.println("Fichier créé avec succès !");
    } else {
      Serial.println("Échec de la création du fichier !");
    }
  }


  dataFile = SD.open(filenameDonnees, FILE_WRITE);
  paraFile = SD.open(filenamePara, FILE_WRITE);
    //dataFile.println("");
  

   if (readParameters(filenamePara)) {
    Serial.println("Parameters read successfully:");
    for (int i = 0; i < N; i++) {
      Serial.print("Parameter ");
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.println(parameters[i]);
    }
  } else {
    Serial.println("Failed to read parameters.");
  }

/*
  /*
    if (!createDefaultFile("parametresSysteme.csv")) {
      Serial.println("Error creating the default file.");
      lcd.setCursor(0, 0);  
      lcd.print("ERREUR TERMINALE"); // RIP
      while(true);
    }
    
  }

*/
}



/*
void lireDonneesSD(const char* nomFichier) {
    File fichier = SD.open(filenamePara);
    if (!fichier) {
        Serial.println("Erreur : impossible d'ouvrir le fichier.");
        return;
    }

    Serial.println("Contenu du fichier :");
    while (fichier.available()) {
        
        






        
    }
    fichier.close();
}



*/


void generateRandomFloats() {
  for (int i = 0; i < numFloats; i++) {
    // Generate a random float between 0 and 100
    randomFloats[i] = random(0, 101) + random(0, 1000) / 1000.0;
    
    // Store the float in EEPROM
    int address = eepromStartAddress + i * sizeof(float);
    byte* floatBytes = (byte*)(&randomFloats[i]);
    for (int j = 0; j < sizeof(float); j++) {
      EEPROM.write(address++, floatBytes[j]);
    }
  }
  Serial.println("Random floats stored in EEPROM.");
}





void retrieveFloatsFromEEPROM() {
  int address = eepromStartAddress;


  for (int i = 0; i < sdN; i++) {
    byte floatBytes[sizeof(float)];
    for (int j = 0; j < sizeof(float); j++) {
      float data = EEPROM.read(address++);
      if(isnan(data)){
        data = 5;
      }
      floatBytes[j] = data;
    }
    donneesSD[i] = *((float*)floatBytes);
  }
Serial.println("!!!!");
    
   // Serial.println( donneesSD]0]);
    delay(2000);
  }




void updateParaData(){
int st = eepromStartAddress;
Serial.println("lalala");
 for (int i = 0; i < sdN; i++) {
    byte* floatBytes = (byte*)(donneesSD + i);
    for (int j = 0; j < sizeof(float); j++) {
      EEPROM.update(st++, floatBytes[j]);
      Serial.println("witing");
      Serial.println(floatBytes[j]);
   

    }
  }

}


/*
void updateParaData() {
 /* paraFile.print("\n");
   
  for(int i = 0; i < sdN; i++){

    paraFile.print(String(donneesSD[i])+ ",");
    
  }

  paraFile.flush();
  /*
  // Supprimer le fichier existant pour écrire une nouvelle version
  if (SD.exists(filenamePara)) {
    SD.remove(filenamePara);
  }

  // Créer ou ouvrir le fichier pour écriture
  File file = SD.open(filenamePara, FILE_WRITE);
  if (file) {
    Serial.print("Mise à jour du fichier avec : ");
    for (int i = 0; i < sdN; i++) {
      file.print(donneesSD[i]); // Écrire les valeurs
      Serial.print(donneesSD[i]); // Afficher les valeurs dans le moniteur série
      if (i < sdN - 1) {
        file.print(","); // Ajouter une virgule entre les valeurs
        Serial.print(",");
      }
    }
    file.println(); // Terminer la ligne
    Serial.println();
    file.close(); // Fermer le fichier
    Serial.println("Mise à jour terminée !");
  } else {
    Serial.println("Échec de l'ouverture/création du fichier !");
  }
  */






/*
bool loadDataFromSD(const char* fileName) {
  if (!SD.exists(fileName)) {
    Serial.println("File does not exist.");
    return false; // File not found
  }

  File dataFile = SD.open(fileName, FILE_READ);
  if (!dataFile) {
    Serial.println("Error opening file for reading.");
    return false;
  }

  Serial.println("Reading file...");
  for (int i = 0; i < N; i++) {
    if (dataFile.available()) {
      String variableStr = dataFile.readStringUntil(',');
      donneesSD[i] = variableStr.toFloat(); // Convert string to float
    } else {
      donneesSD[i] = 0.0; // Default if file has fewer variables
    }
    Serial.print("Variable ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(donneesSD[i]);
  }
  dataFile.close();
  return true;
}


bool createDefaultFile(const char* fileName) {
  File dataFile = SD.open(fileName, FILE_WRITE);
  if (!dataFile) {
    Serial.println("Error creating the default file.");
    return false;
  }

  Serial.println("Creating default file...");
  for (int i = 0; i < N; i++) {
    dataFile.print(donneesSD[i], 2); // Write with 2 decimal places
    if (i < N - 1) dataFile.print(","); // Add commas between variables
  }
  dataFile.println(); // End the line
  dataFile.close();
  return true;
}

// Function to update a specific variable in the array
void updateVariable(int index, float newValue) {
  if (index >= 0 && index < N) {
    donneesSD[index] = newValue;
    Serial.print("Updated variable ");
    Serial.print(index);
    Serial.print(" to ");
    Serial.println(newValue);
  } else {
    Serial.println("Error: Index out of range.");
  }
}



bool saveDataToSD(const char* fileName) {
  // Delete the old file
  if (SD.exists(fileName)) {
    if (!SD.remove(fileName)) {
      Serial.println("Error deleting old file.");
      return false;
    }
  }

  // Create a new file
  File dataFile = SD.open(fileName, FILE_WRITE);
  if (!dataFile) {
    Serial.println("Error creating new file.");
    return false;
  }

  Serial.println("Writing to new file...");
  for (int i = 0; i < N; i++) {
    dataFile.print(donneesSD[i], 2); // Write with 2 decimal places
    if (i < N - 1) dataFile.print(","); // Add commas between variables
  }
  dataFile.println(); // End the line
  dataFile.close();
  return true;
}

*/

