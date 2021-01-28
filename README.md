<h1>Nodemcu-Clock-with-DHT22-temperature-and-humidity-and-Spotify-now-playing</h1>
<p>&nbsp;</p>
<p>Esp8266/Nodemcu sketch to check the Temperature and Humidity from a DHT22 sensor, get the local time from NTP server and data from a spotify account and display them on an .96" Oled screen. Works with DHT11 also.</p>
<p>Instructions:</p>
<p><strong>#What you will need:</strong></p>
<ol>
  <li>
    <p>Esp8266/Nodemcu microcontroller or similar</p>
  </li>
  <li>
    <p>0.96'' Oled screen</p>
  </li>
  <li>
    <p>DHT22 sensor (DHT11 and DHT21 should work also, you just need to define your model on the code)</p>
  </li>
  <li>
    <p>3D printer (optional)</p>
  </li>
</ol>
<p><strong>#Instructions</strong></p>
<h3>Spotify Account</h3>
<ul>
  <li>Sign into the <a href="https://developer.spotify.com/dashboard/login" rel="nofollow">Spotify Developer page</a></li>
  <li>Create a new application. (name it whatever you want)</li>
  <li>You will need to use the "client ID" and "client secret" from this page in your sketches</li>
  <li>You will also need to add a callback URI for authentication process by clicking "Edit Settings", what URI to add will be mentioned in further instructions</li>
</ul>
<h3>Getting Your Refresh Token</h3>
<p>Spotify's Authentication flow requires a webserver to complete, but it's only needed once to get your refresh token. Your refresh token can then be used in all future sketches to authenticate.</p>
<p>Because the webserver is only needed once, I decided to seperate the logic for getting the Refresh token to it's own examples.</p>
<p>Follow the instructions in one of the following examples to get your token.</p>
<ul>
  <li><a href="https://github.com/lon3wolf2k/Nodemcu-Clock-with-DHT22-temperature-and-humidity-and-Spotify-now-playing/blob/main/getRefreshToken.ino">ESP8266</a></li>
</ul>
<p>&nbsp;</p>
<p>Enter all the above in the sketch plus your wifi credentials Make sure you have all the necessary libraries installed. </p>
<p>Dont forget to set offset time in seconds to adjust for your timezone, for example:<br>
  GMT +1 = 3600<br>
  GMT +8 = 28800<br>
  GMT -1 = -3600<br>
  GMT 0 = 0<br>
Use the following formula to calculate if GMT+2 then offset is 2x60x60=7200</p>
<p><strong>Wire Connections: </strong></p>
<p>DHT22 data to D5-GPIO14 VCC to 3.3v and GND to GND,</p>
<p> OLED's SCK goes to D1-GPIO5 and SDA to D2-GPIO4</p>
<p>&nbsp;</p>
<p>Made possible with the following examples and files:</p>
<p><a href="https://github.com/witnessmenow/arduino-spotify-api">https://github.com/witnessmenow/arduino-spotify-api</a></p>
<p><a href="https://randomnerdtutorials.com/esp8266-nodemcu-date-time-ntp-client-server-arduino/">https://randomnerdtutorials.com/esp8266-nodemcu-date-time-ntp-client-server-arduino/</a></p>
<p>&nbsp;</p>
<p>3d files from:</p>
<p><a href="https://www.thingiverse.com/thing:2670123">https://www.thingiverse.com/thing:2670123</a></p>
<img src="./photo1.jpg">
<img src="./photo2.jpg">
<img src="./photo3.jpg">

