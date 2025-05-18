#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "Adafruit_PM25AQI.h"
#include <HardwareSerial.h>

// LCD1602 I2C
LiquidCrystal_I2C lcd(0x27, 16, 2);

// PMS5003 on Serial2
HardwareSerial pmSerial(2);
Adafruit_PM25AQI aqi = Adafruit_PM25AQI();

void setup() {
  Serial.begin(115200);
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Initializing...");

  // Serial2 for PMS5003
  pmSerial.begin(9600, SERIAL_8N1, 16, 17); // RX=16, TX=17

  if (!aqi.begin_UART(&pmSerial)) {
    lcd.clear();
    lcd.print("Sensor failed");
    while (1) delay(10);
  }

  lcd.clear();
  lcd.print("PM2.5 Monitor");
  delay(2000);
}

void loop() {
  PM25_AQI_Data data;

  if (aqi.read(&data)) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("PM2.5: ");
    lcd.print(data.pm25_standard);
    lcd.print(" ug/m3");

    lcd.setCursor(0, 1);
    lcd.print("PM10 : ");
    lcd.print(data.pm10_standard);
    lcd.print(" ug/m3");
  } else {
    lcd.setCursor(0, 0);
    lcd.print("No Data");
  }

  delay(2000); // อ่านทุก 2 วินาที
}
