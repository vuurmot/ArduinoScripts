#include <LiquidCrystal.h>

#define sensorPin A0

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int prevSensorVal;
int calibratedOffset;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("Calibrating sensor....");

  while (millis() < 5000) {
    int averageSensorVal = readSensor();
    prevSensorVal = (prevSensorVal + averageSensorVal) / 2;
  }
  calibratedOffset = prevSensorVal - 400;
}

void loop() {
  delay(500);
  lcd.clear();
  lcd.setCursor(0, 0);
  int currentGasPPM = readSensor() - calibratedOffset;

  if (currentGasPPM > 500) {
    lcd.print("Curr PPM (BAD) ");
  } else {
    lcd.print("Curr PPM (GOOD) ");
  }
  lcd.setCursor(0, 1);
  lcd.print(currentGasPPM);
}

int readSensor() {
  unsigned int sensorValue = analogRead(sensorPin);
  return sensorValue;
}