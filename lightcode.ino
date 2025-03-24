#include <WiFiNINA.h>
#include <ArduinoHttpClient.h>


char ssid[] = "Samsung";
char pass[] = "hihahiha";


const char* server = "maker.ifttt.com";
String IFTTT_Key = "kmeLtIhf2OqlmlmXDCOgSkKmJ4GUDwwYrptBGsYcTQ9";
int lightPin = A0;
int threshold = 1; 

WiFiClient wifi;
HttpClient client = HttpClient(wifi, server, 80);

bool wasBright = false;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  connectWiFi();
}

void loop() {
  int lightValue = analogRead(lightPin);
  Serial.println(lightValue);

  if (lightValue > threshold && !wasBright) {
    sendToIFTTT("sunlight_on");
    wasBright = true;
  } else if (lightValue <= threshold && wasBright) {
    sendToIFTTT("sunlight_off");
    wasBright = false;
  }

  delay(10000); 
}

void connectWiFi() {
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    Serial.println("Connecting...");
    delay(1000);
  }
  Serial.println("Connected to WiFi!");
}

void sendToIFTTT(String eventName) {
  String url = "/trigger/" + eventName + "/with/key/" + IFTTT_Key;
  Serial.print("Triggering event: ");
  Serial.println(eventName);

  client.get(url);

  int statusCode = client.responseStatusCode();
  String response = client.responseBody();
  Serial.print("Status: ");
  Serial.println(statusCode);
  Serial.print("Response: ");
  Serial.println(response);
}
