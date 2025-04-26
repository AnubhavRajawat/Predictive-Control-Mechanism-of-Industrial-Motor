#include <WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include <Adafruit_ADXL345_U.h>
#include <DHT.h>

// WiFi credentials
const char* ssid = "UserName";
const char* password = "Password";

// MQTT broker IP
const char* mqtt_server = "Broker IP";

WiFiClient espClient;
PubSubClient client(espClient);

// ADXL345 sensor
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

// Sensor pins
#define proximityPin 25
#define lm35Pin 32
#define DHTPIN 4        // GPIO pin connected to DHT22
#define DHTTYPE DHT22    // DHT 22 (AM2302)

// RPM variables
volatile int pulseCount = 0;
unsigned long lastRPMTime = 0;
int rpm = 0;

// DHT sensor instance
DHT dht(DHTPIN, DHTTYPE);

void IRAM_ATTR countPulse() {
  pulseCount++;
}

void setup_wifi() {
  delay(100);
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected.");
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("ESP32_MotorMonitor")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);

  if (!accel.begin()) {
    Serial.println("ADXL345 not found, check wiring!");
    while (1);
  }
  accel.setRange(ADXL345_RANGE_2_G);

  pinMode(proximityPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(proximityPin), countPulse, FALLING);

  dht.begin(); // Initialize DHT22
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Read ADXL345 data
  sensors_event_t event;
  accel.getEvent(&event);

  // Read LM35 temperature
  int lm35Raw = analogRead(lm35Pin);
  float voltage = (lm35Raw / 4095.0) * 3.3;
  float temperatureC = voltage * 100;

  // Read DHT22 temperature and humidity
  float dhtTemp = dht.readTemperature();
  float dhtHum = dht.readHumidity();

  // Calculate RPM every 2 seconds
  unsigned long currentTime = millis();
  if (currentTime - lastRPMTime >= 2000) {
    rpm = (pulseCount * 30);
    pulseCount = 0;
    lastRPMTime = currentTime;
  }

  // Publish MQTT data
  client.publish("motor/vibration/x", String(event.acceleration.x).c_str());
  client.publish("motor/vibration/y", String(event.acceleration.y).c_str());
  client.publish("motor/vibration/z", String(event.acceleration.z).c_str());
  client.publish("motor/tempC", String(temperatureC).c_str());
  client.publish("motor/rpm", String(rpm).c_str());

  // DHT22 MQTT topics
  if (!isnan(dhtTemp)) {
    client.publish("motor/dht/tempC", String(dhtTemp).c_str());
  }
  if (!isnan(dhtHum)) {
    client.publish("motor/dht/humidity", String(dhtHum).c_str());
  }

  // Serial Monitor Output
  Serial.println("===== Sensor Readings =====");
  Serial.print("Vibration X: "); Serial.print(event.acceleration.x); Serial.println(" m/s²");
  Serial.print("Vibration Y: "); Serial.print(event.acceleration.y); Serial.println(" m/s²");
  Serial.print("Vibration Z: "); Serial.print(event.acceleration.z); Serial.println(" m/s²");
  Serial.print("LM35 Temp: "); Serial.print(temperatureC); Serial.println(" °C");
  Serial.print("RPM: "); Serial.println(rpm);
  Serial.print("DHT22 Temp: "); Serial.print(dhtTemp); Serial.println(" °C");
  Serial.print("DHT22 Humidity: "); Serial.print(dhtHum); Serial.println(" %");
  Serial.println("============================\n");

  delay(2000);
}