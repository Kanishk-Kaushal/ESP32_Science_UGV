#include <WiFi.h>

// Replace with your network credentials
const char* ssid = "Kanishk";
const char* password = "oneplus9";

// Defines Client
WiFiClient client;

// Set web server port number to 5005
WiFiServer server(5005);

// Set your Static IP address
IPAddress local_IP(192, 168, 1, 134);

// Set your Gateway IP address
IPAddress gateway(192, 168, 1, 1);

// Set your Subnet
IPAddress subnet(255, 255, 255, 0);

// Set your Primary DNS
IPAddress primaryDNS(8, 8, 8, 8);   // Optional

// Set your Secondary DNS
IPAddress secondaryDNS(8, 8, 4, 4); // Optional

// Right Motor
int rpwm = 36;    // D23
int rdir = 39;    // D22
int dr = 0;       // dr -> Right Direction Scraped Value
uint16_t rdc = 0; // rdc -> Right Duty Cycle

// Left Motor
int lpwm = 42; // D21
int ldir = 38; // D19
int dl = 0;       // dl -> Left Direction Scraped Value
uint16_t ldc = 0; // ldc -> Left Duty Cycle


// Setting Right PWM properties
const int RightFreq = 30000;
const int RightPWMChannel = 0;
const int RightResolution = 8;
const int RIGHT_MAX_DUTY_CYCLE = (int)(pow(2, RightResolution) - 1);


// Setting Left PWM properties
const int LeftFreq = 30000;
const int LeftPWMChannel = 2;
const int LeftResolution = 8;
const int LEFT_MAX_DUTY_CYCLE = (int)(pow(2, LeftResolution) - 1);

void setup() 
{
  Serial.begin(115200);

  // Configures static IP Address
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) 
  {
    Serial.println("STA Failed to configure");
  }

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print("Connecting... ");
  }
  
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi Successfully Connected. \n");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
  
  // Sets the pins as outputs:
  pinMode(rpwm, OUTPUT);
  pinMode(rdir, OUTPUT);
  pinMode(lpwm, OUTPUT);
  pinMode(ldir, OUTPUT);
   
  // Configure RIght LED PWM functionalitites
  ledcSetup(RightPWMChannel, RightFreq, RightResolution);

  // Configure Left LED PWM functionalitites
  ledcSetup(LeftPWMChannel, LeftFreq, LeftResolution);
  
  // Attach the channel to the GPIO to be controlled
  ledcAttachPin(rpwm, RightPWMChannel);
  ledcAttachPin(lpwm, LeftPWMChannel);

}

void loop() 
{
  client = server.available();
  if(client == 1)
  {

    while(1)
    {
      String request = client.readStringUntil('e');
      request.trim();
      
      if (request[0] == 'm')
      {
        rdc = (request[1]-'0')*100 + (request[2]-'0')*10 + (request[3]-'0');
        ledcWrite(RightPWMChannel, rdc);

        dr = request[4]-'0';
        if(dr == 1)
        {
          digitalWrite(rdir, HIGH);
        }
        else
        {
          digitalWrite(rdir, LOW);
        }
        

        ldc = (request[5]-'0')*100 + (request[6]-'0')*10 + (request[7]-'0');
        ledcWrite(LeftPWMChannel, ldc);


        dl = request[8]-'0';
        if(dl == 1)
        {
          digitalWrite(ldir, HIGH);
        }
        else
        {
          digitalWrite(ldir, LOW);
        }
        
 
        Serial.println("PWMR");
        Serial.println(rdc);
        Serial.println("PWML");
        Serial.println(ldc);
        Serial.println("DIRR");
        Serial.println(dr);
        Serial.println("DIRL");
        Serial.println(dl);
      }
      
     else if(request[9] == 'e')
      {
        break;
      }
  
    }
  
  }

}
