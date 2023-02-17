# How to convert Philips DS1150/12 into ESP32 Internet Radio

### Original Philips DS1150/12
<img src="https://raw.githubusercontent.com/petervflocke/ESP32Radio-V2PvF/master/Philips_DS1150/Philips-DS1150.jpeg" width="500">

### Modified:
<img src="https://raw.githubusercontent.com/petervflocke/ESP32Radio-V2PvF/master/Philips_DS1150/Fidelio-InternetRadio.jpg" width=500>


## Cookbook: Description in progress ...

Before you start read the ... [manual from Ed](../doc/ESP32-radio.odt)
TL;DR? Then here is a quick list of tasks:

1. Clone this repo locally. Update platformio.ini to reflect your ESP32 board config 
    ```
    board = ?????
    ;upload_protocol = espota
    ;upload_port = 192.168.0.165
    upload_port = /dev/ttyUSB0
    ```
    Comment out OTA/espota protokol and network IP. Check your serial port, etc, make it working with your board over USB/serial.

2. From `data` folder create file system and upload it your ESP32

    2.1. Use platformIO project tasks: Build Filesystem Image

    2.2. Use platformIO project tasks: Upload File System Image

3. Uncomment and correct in the `include/config.h` file your WiFi credentials

    ```#define FIXEDWIFI "SSID/YourWiFi Password"```


4. Connect VS1053 module to ESP. To find out ESP32 pins and wiring

    4.1 Use [wiring](Philips_DS1150/PhilipsESP32Radio.png) or

    4.2 Use [Config](include/config.txt)

    4.3 Or this table:

    | ESP32   | VS1003 VS1053   |
    | ------- | ----------------|
    | GPIO16  | 1 DCS/XDCS      |
    | GPIO5   | 2 CS/XCS        |
    | EN      | 3 XRESET        |
    | GPIO4   | 4 DREQ          |
    | GPIO18  | 5 SCK           |
    | GPIO23  | 6 MOSI          |
    | GPIO19  | 7 MISO          |
    | GND     | 8 GND           |
    | VCC     | 9 5V            |

5. Do not connect anything else! Upload the code to ESP32, turn on serial monitoring, find out on the serial console your local IP ESP was granted from your DHCP/router.

6. Open IP address of your newly started ESP32Radio in your internet browser, go to Config page and paste the content of the [Config](include/config.txt) file. Update your WiFi SSID/password there. Save it.

7. Restart Module, and monitor your serial console