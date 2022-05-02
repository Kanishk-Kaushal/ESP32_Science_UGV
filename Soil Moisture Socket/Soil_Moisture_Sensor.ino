#include <WiFi.h>

// ANALOG INPUT PIN
int sensor_pin = 36;

int value ;

// COLLABORATIVE FACTORS
int dry_air_val = 4095;
int water_val = 1240;

// NETWORK CONFIGURATION
const char* ssid = "wifi";
const char* password =  "password";

// PORT NUMBER
const uint16_t port = 8090;

// HOST IP ADDRESS
// Do "ipconfig" on the host laptop and find its IP
const char * host = "192.168.156.246";

// DATA TO TRANSFER
String test = "Hello from ESP32!";


void setup()
{

  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("...");
  }

  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());

  Serial.println("Reading from Soil Moisture Sensor");

}

void loop()
{
    WiFiClient client;

    if (!client.connect(host, port)) {

        Serial.println("Connection to host failed");

        delay(1000);
        return;
    }

    Serial.println("Connected to server successful!");

    value = analogRead(sensor_pin);
    value = map(value, dry_air_val, water_val, 0, 100);

    Serial.print("Moisture : ");
    Serial.print(value);
    Serial.println("%");
    
    client.print(value);

    Serial.println("Disconnecting...");
    client.stop();

    delay(1000);
}
