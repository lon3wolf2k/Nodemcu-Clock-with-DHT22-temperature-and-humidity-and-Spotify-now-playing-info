// ----------------------------
// Standard Libraries
// ----------------------------

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

// ----------------------------
// Additional Libraries - each one of these will need to be installed.
// ----------------------------

#include <ArduinoSpotify.h>
// Library for connecting to the Spotify API

// Install from Github
// https://github.com/witnessmenow/arduino-spotify-api

#include <ArduinoJson.h>
// Library used for parsing Json from the API responses

// Search for "Arduino Json" in the Arduino Library manager
// https://github.com/bblanchon/ArduinoJson

//------- Replace the following! ------

char ssid[] = "";         // your network SSID (name)
char password[] = ""; // your network password

char clientId[] = ""; // Your client ID of your spotify APP
char clientSecret[] = ""; // Your client Secret of your spotify APP (Do Not share this!)

// Country code, including this is advisable
#define SPOTIFY_MARKET "IE"

#define SPOTIFY_REFRESH_TOKEN ""


//------- ---------------------- ------

WiFiClientSecure client;
ArduinoSpotify spotify(client, clientId, clientSecret, SPOTIFY_REFRESH_TOKEN);

unsigned long delayBetweenRequests = 1000; // Time between requests (1 minute)
unsigned long requestDueTime;               //time when request due

/* TIMER */
#include <SimpleTimer.h>
SimpleTimer timer;

//Screen and Temp sensor Libraries
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include "DHT.h"


//Screen and Temp sensor Libraries
#include <NTPClient.h>
#include <WiFiUdp.h>

const long utcOffsetInSeconds = 7200;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

//Define Screen dimensions
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//Define Sensor Pins and Type
#define DHTPIN 14     // what pin we're connected to
//Choose Sensor Type
#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino

//Variables
int chk;
float hum;  //Stores humidity value
float temp; //Stores temperature value


void setup() {
  Serial.begin(115200);
  dht.begin();
  timeClient.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  delay(2000);
  display.clearDisplay();
  display.setTextColor(WHITE);
  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);

  // Only avaible in ESP8266 V2.5 RC1 and above
  client.setFingerprint(SPOTIFY_FINGERPRINT);

  // If you want to enable some extra debugging
  // uncomment the "#define SPOTIFY_DEBUG" in ArduinoSpotify.h

  Serial.println("Refreshing Access Tokens");
  if (!spotify.refreshAccessToken()) {
    Serial.println("Failed to get access tokens");
  }

}
void printCurrentlyPlayingToSerial(CurrentlyPlaying currentlyPlaying)
{
  if (!currentlyPlaying.error)
  {
    Serial.println("--------- Currently Playing ---------");


    Serial.print("Is Playing: ");
    if (currentlyPlaying.isPlaying)
    {
      Serial.println("Yes");
    } else {
      Serial.println("No");
    }

    Serial.print("Track: ");
    Serial.println(currentlyPlaying.trackName);
    Serial.print("Artist: ");
    Serial.println(currentlyPlaying.firstArtistName);
    Serial.println();


    // clear display
    display.clearDisplay();
    if (currentlyPlaying.isPlaying)
    {
      // display Track
      display.setTextSize(2);
      display.setCursor(0, 0);
      display.print("Playing: ");
      display.setTextSize(2);
      display.setCursor(0, 18);
      display.print(currentlyPlaying.trackName);
      display.display();

      delay(5000); //Delay 5 sec.

      // clear display
      display.clearDisplay();

      // display Artist
      display.setTextSize(2);
      display.setCursor(0, 0);
      display.print("By: ");
      display.setTextSize(2);
      display.setCursor(0, 18);
      display.print(currentlyPlaying.firstArtistName);
      display.display();
    } else {
      // No Music Data

    }
  }


}
void loop() {
  timer.run(); // Initiates SimpleTimer
  timeClient.update();

  //Read data and store it to variables hum and temp
  hum = dht.readHumidity();
  temp = dht.readTemperature();

  Serial.print(daysOfTheWeek[timeClient.getDay()]);
  Serial.print(", ");
  Serial.print(timeClient.getHours());
  Serial.print(":");
  Serial.print(timeClient.getMinutes());
  Serial.print(":");
  Serial.println(timeClient.getSeconds());
  //Serial.println(timeClient.getFormattedTime());

  delay(1000);
  //Print temp and humidity values to serial monitor
  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.print(" %, Temp: ");
  Serial.print(temp);
  Serial.println(" Celsius");
  if (millis() > requestDueTime)
  {

    Serial.println("getting currently playing song:");
    // Market can be excluded if you want e.g. spotify.getCurrentlyPlaying()
    CurrentlyPlaying currentlyPlaying = spotify.getCurrentlyPlaying(SPOTIFY_MARKET);

    printCurrentlyPlayingToSerial(currentlyPlaying);

    requestDueTime = millis() + delayBetweenRequests;
  }
  delay(5000); //Delay 5 sec.

  // clear display
  display.clearDisplay();

  // display time
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print(daysOfTheWeek[timeClient.getDay()]);
  display.setTextSize(4);
  display.setCursor(0, 20);
  display.print(timeClient.getHours());
  display.print(":");
  display.print(timeClient.getMinutes());
  display.display();

  delay(5000); //Delay 5 sec.

  // clear display
  display.clearDisplay();

  // display temperature
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print("Temp");
  display.setTextSize(5);
  display.setCursor(0, 20);
  display.print(temp, 0);
  display.setTextSize(2);
  display.print((char)247);
  display.setTextSize(5);
  display.print("C");
  display.display();

  delay(5000); //Delay 5 sec.

  // clear display
  display.clearDisplay();

  // display humidity
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print("Humidity");
  display.setTextSize(5);
  display.setCursor(0, 20);
  display.print(hum, 0);
  display.print(" %");

  display.display();



}
