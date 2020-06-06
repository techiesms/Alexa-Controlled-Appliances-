/*
   This is a basic example on how to use Espalexa and its device declaration methods.

   This code is edited for controlling 4 Appliances by
   Sachin Soni 
   for techiesms YouTube channel 

   You can visit the channel to see
   complete tutorial on making this project
   by yoursleves

   YouTube Channel :- https://www.youtube.com/techiesms


          techiesms
   explore | learn | share
*/

#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <Espalexa.h>


#define R1 15
#define R2 2
#define R3 4
#define R4 22

// prototypes
boolean connectWifi();

//callback functions
void firstLightChanged(uint8_t brightness);
void secondLightChanged(uint8_t brightness);
void thirdLightChanged(uint8_t brightness);
void fourthLightChanged(uint8_t brightness);

// Change this!!

// WiFi Credentials
const char* ssid = "SmS_jiofi";
const char* password = "sms123458956";

// device names
String Device_1_Name = "Office light";
String Device_2_Name = "Studio light";
String Device_3_Name = "Yellow Bulb";
String Device_4_Name = "Red bulb";

boolean wifiConnected = false;

Espalexa espalexa;

void setup()
{
  Serial.begin(115200);

  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(R3, OUTPUT);
  pinMode(R4, OUTPUT);

  // Initialise wifi connection
  wifiConnected = connectWifi();

  if (wifiConnected)
  {

    // Define your devices here.
    espalexa.addDevice(Device_1_Name, firstLightChanged); //simplest definition, default state off
    espalexa.addDevice(Device_2_Name, secondLightChanged);
    espalexa.addDevice(Device_3_Name, thirdLightChanged);
    espalexa.addDevice(Device_4_Name, fourthLightChanged);

    espalexa.begin();

  }

  else
  {
    while (1)
    {
      Serial.println("Cannot connect to WiFi. Please check data and reset the ESP.");
      delay(2500);
    }
  }

}

void loop()
{
  espalexa.loop();
  delay(1);
}

//our callback functions
void firstLightChanged(uint8_t brightness)
{
  //Control the device
  if (brightness)
  {
    if (brightness == 255)
    {
      digitalWrite(R1, HIGH);
      Serial.println("Device1 ON");
    }
    //Serial.print("ON, brightness ");
    //Serial.println(brightness);
  }
  else
  {
    digitalWrite(R1, LOW);
    Serial.println("Device1 OFF");
  }
}

void secondLightChanged(uint8_t brightness)
{

  //Control the device 
  if (brightness)
  {
    if (brightness == 255)
    {
      digitalWrite(R2, HIGH);
      Serial.println("Device2 ON");
    }
    //Serial.print("ON, brightness ");
    //Serial.println(brightness);
  }
  else
  {
    digitalWrite(R2, LOW);
    Serial.println("Device2 OFF");
  }
}

void thirdLightChanged(uint8_t brightness)
{

  //Control the device  
  if (brightness)
  {
    if (brightness == 255)
    {
      digitalWrite(R3, HIGH);
      Serial.println("Device3 ON");
    }
    //Serial.print("ON, brightness ");
    //Serial.println(brightness);
  }
  else
  {
    digitalWrite(R3, LOW);
    Serial.println("Device3 OFF");
  }
}

void fourthLightChanged(uint8_t brightness)
{

  //Control the device 
  if (brightness)
  {

    if (brightness == 255)
    {
      digitalWrite(R4, HIGH);
      Serial.println("Device4 ON");
    }
    //Serial.print("ON, brightness ");
    //Serial.println(brightness);
  }
  else
  {
    digitalWrite(R4, LOW);
    Serial.println("Device4 OFF");
  }
}

// connect to wifi – returns true if successful or false if not
boolean connectWifi()
{
  boolean state = true;
  int i = 0;

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 20) {
      state = false; break;
    }
    i++;
  }
  Serial.println("");
  if (state) {
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("Connection failed.");
  }
  return state;
}
