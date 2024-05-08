#include <LiquidCrystal.h>
#include <DHT.h>

const int soilMoisturePin = A0; // Analog pin connected to the soil moisture sensor
const int ldrPin = A1;          // Analog pin connected to the LDR
const int irSensorPin = 2;      // Digital pin connected to the IR sensor
const int relayPin = 10;        // Digital pin connected to the relay module
const int ledPin = 13;          // Digital pin connected to the LED

#define DHTPIN 3                 // Digital pin connected to the DHT sensor
#define DHTTYPE DHT11            // DHT sensor type

DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // LCD pin configuration: rs, en, d4, d5, d6, d7

void setup() {
  pinMode(soilMoisturePin, INPUT); // Set soil moisture pin as input
  pinMode(ldrPin, INPUT);           // Set LDR pin as input
  pinMode(irSensorPin, INPUT);      // Set IR sensor pin as input
  pinMode(relayPin, OUTPUT);        // Set relay pin as output
  pinMode(ledPin, OUTPUT);          // Set LED pin as output
  
  lcd.begin(16, 2);   // Initialize the LCD with 16 columns and 2 rows
  Serial.begin(9600); // Initialize serial communication at 9600 baud
  dht.begin();        // Initialize the DHT sensor
}

void loop() {
  // Read sensor data
  int soilMoisture = analogRead(soilMoisturePin); // Read soil moisture value
  int ldrValue = analogRead(ldrPin);              // Read LDR value
  int irSensorValue = digitalRead(irSensorPin);    // Read IR sensor value
  float humidity = dht.readHumidity();             // Read humidity value
  float temperature = dht.readTemperature();       // Read temperature value in Celsius
  
  // Display LDR value on LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("LDR Value: ");
  lcd.print(ldrValue);
  
  // Display DHT data on LCD
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print("C  Humidity: ");
  lcd.print(humidity);
  lcd.print("%");
  
  // If moisture level is low, turn on the relay
  if (soilMoisture < 300) {
    digitalWrite(relayPin, HIGH);
  } else {
    digitalWrite(relayPin, LOW);
  }

  // If IR sensor is high, turn on the LED
  if (irSensorValue == HIGH) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  // Print sensor values to serial monitor for debugging
  Serial.print("Soil Moisture: ");
  Serial.print(soilMoisture);
  Serial.print(", LDR Value: ");
  Serial.print(ldrValue);
  Serial.print(", IR Sensor Value: ");
  Serial.print(irSensorValue);
  Serial.print(", Temperature: ");
  Serial.print(temperature);
  Serial.print("C, Humidity: ");
  Serial.print(humidity);
  Serial.println("%");

  delay(1000); // Delay before next reading (adjust as needed)
}
