#include <LiquidCrystal.h>

// -------- LCD Parallel Connections --------
// RS -> GPIO14
// EN -> GPIO27
// D4 -> GPIO18
// D5 -> GPIO19
// D6 -> GPIO23
// D7 -> GPIO22
LiquidCrystal lcd(14, 27, 18, 19, 23, 22);

// -------- Pins --------
const int relayPin  = 25;   // Relay IN -> GPIO25
const int buzzerPin = 26;   // Buzzer + -> GPIO26
const int acsPin    = 34;   // ACS712 OUT -> GPIO34

// -------- ACS712 Settings --------
// ACS712 5A version sensitivity = 185mV/A
const float sensitivity = 0.185;
const float adcRef = 3.3;
const int adcMax = 4095;

// -------- Threshold --------
// Change this value based on your load current
const float currentThreshold = 0.80;   // in Amps

// -------- Relay Logic --------
// Many relay modules are active LOW
const int RELAY_ON  = LOW;
const int RELAY_OFF = HIGH;

float zeroCurrentVoltage = 1.65;

void setup() {
  Serial.begin(115200);

  pinMode(relayPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  digitalWrite(relayPin, RELAY_ON);
  digitalWrite(buzzerPin, LOW);

  lcd.begin(16, 2);

  lcd.setCursor(0, 0);
  lcd.print("Power Theft");
  lcd.setCursor(0, 1);
  lcd.print("System Start");
  delay(2000);

  zeroCurrentVoltage = calibrateACS712();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("System Ready");
  delay(1500);
  lcd.clear();
}

void loop() {
  float currentValue = readCurrent();

  Serial.print("Current = ");
  Serial.print(currentValue, 3);
  Serial.println(" A");

  if (currentValue > currentThreshold) {
    digitalWrite(buzzerPin, HIGH);
    digitalWrite(relayPin, RELAY_OFF);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("THEFT DETECTED");
    lcd.setCursor(0, 1);
    lcd.print("Power Cut OFF");
  } 
  else {
    digitalWrite(buzzerPin, LOW);
    digitalWrite(relayPin, RELAY_ON);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Current:");
    lcd.print(currentValue, 2);
    lcd.print("A");

    lcd.setCursor(0, 1);
    lcd.print("Status:NORMAL ");
  }

  delay(500);
}

float readCurrent() {
  const int samples = 200;
  long sum = 0;

  for (int i = 0; i < samples; i++) {
    sum += analogRead(acsPin);
    delay(2);
  }

  float avgADC = sum / (float)samples;
  float sensorVoltage = (avgADC * adcRef) / adcMax;

  float current = (sensorVoltage - zeroCurrentVoltage) / sensitivity;

  if (current < 0) {
    current = -current;
  }

  if (current < 0.05) {
    current = 0.0;
  }

  return current;
}

float calibrateACS712() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Calibrating...");
  lcd.setCursor(0, 1);
  lcd.print("No Load");

  const int samples = 500;
  long sum = 0;

  for (int i = 0; i < samples; i++) {
    sum += analogRead(acsPin);
    delay(2);
  }

  float avgADC = sum / (float)samples;
  float voltage = (avgADC * adcRef) / adcMax;

  Serial.print("Zero Current Voltage = ");
  Serial.println(voltage, 4);

  delay(1000);
  return voltage;
}