const int hallPin = A0;

float flowRate = 5.0;      // L/min (assumed for prototype)
float pricePerSCM = 50.0;  // ₹ per SCM

unsigned long startTime = 0;
float gasUsed = 0;         // liters

void setup() {
  Serial.begin(9600);
}

void loop() {
  int hallValue = analogRead(hallPin);

  if (hallValue < 100) {  // magnet detected → burner ON
    if (startTime == 0) startTime = millis();
  } else {                // burner OFF
    if (startTime != 0) {
      float minutes = (millis() - startTime) / 60000.0;
      gasUsed += flowRate * minutes;
      startTime = 0;
    }
  }

  // compute current totals
  float currentGas = gasUsed;
  if (startTime != 0) {
    float minutesOn = (millis() - startTime) / 60000.0;
    currentGas = gasUsed + flowRate * minutesOn;
  }

  float gasSCM = currentGas / 1000.0;
  float bill   = gasSCM * pricePerSCM;
  float secondsOn = (startTime == 0) ? 0 : (millis() - startTime) / 1000.0;

  // send JSON line
  Serial.print("{\"burner\":\"");
  Serial.print(startTime ? "ON" : "OFF");
  Serial.print("\",\"time_sec\":");
  Serial.print(secondsOn);
  Serial.print(",\"gas_l\":");
  Serial.print(currentGas);
  Serial.print(",\"gas_scm\":");
  Serial.print(gasSCM);
  Serial.print(",\"bill_rs\":");
  Serial.print(bill);
  Serial.println("}");

  delay(500);
}
