#include <SPI.h>
#include <WiFiNINA.h>
#include "ThingSpeak.h"
#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT11

char ssid[] = "Samsung";        // replace with your WiFi name
char pass[] = "hihahiha";    // replace with your WiFi password

WiFiClient client;

unsigned long myChannelNumber = YOUR_CHANNEL_NUMBER;
const char * myWriteAPIKey = "N2K9X5CTMIW29DEC"; // from ThingSpeak

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();

  WiFi.begin(ssid, pass);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  ThingSpeak.begin(client);
}

void loop() {
  float temp = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temp) || isnan(humidity)) {
    Serial.println("Sensor failed!");
    return;
  }

  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.print(" °C\tHumidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  ThingSpeak.setField(1, temp);
  ThingSpeak.setField(2, humidity);

  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

  if (x == 200) {
    Serial.println("Data sent to ThingSpeak.");
  } else {
    Serial.print("Error sending data. HTTP code ");
    Serial.println(x);
  }

  delay(60000); // Wait 60 seconds
}
