# A Christmas tree

Hardware: 
  - ESP32
  - SK6812 rgbw leds

Firmware:
  - FastLED for driving the leds
  - khoih-prog/ESPAsync_WiFiManager
    Configuring the wifi capture portal in a performant async way.
  - khoih-prog/ESP_DoubleResetDetector
    Making sure we dont have to configure the wifi every reset, but still are able to do so.
	- https://github.com/me-no-dev/ESPAsyncWebServer.git
    Powering the esp hosted server. Serving the static svelte frontend.  

Web frontend:
  - Powered by svelte-kit
  Build it by running:
    - npm install
    - npm run build
    -> This will update the files in data folder.

  Upload the frontend to the ESP flash by uploading the filesystem image using the platform io cli.