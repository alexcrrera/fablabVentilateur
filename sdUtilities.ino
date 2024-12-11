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



