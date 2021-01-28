# Nodemcu-Clock-with-DHT22-temperature-and-humidity-and-Spotify-now-playing
Nodemcu Clock with DHT22 temperature and humidity and Spotify now playing

Esp8266/Nodemcu sketch to check the Temperature and Humidity from a DHT22 sensor, get the local time from NTP server and data from a spotify account and display them on an .96" Oled screen. Works with DHT11 also.

Instructions:

#What you will need:

Esp8266/Nodemcu microcontroller or similar



0.96'' Oled screen



DHT22 sensor (DHT11 and DHT21 should work also, you just need to define your model on the code)



3D printer (optional)





#Instructions

Enter all the above in the sketch plus your wifi credentials Make sure you have all the necessary libraries installed. Connect DHT22 data to D5-GPIO14 VCC to 3.3v and GND to GND OLED's SCK goes to D1-GPIO5 and SDA to D2-GPIO4
