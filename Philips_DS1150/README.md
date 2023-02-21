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


4. Use a test breadboard and jumper wires / Dupont cables and connect VS1053 module to ESP. To find out ESP32 pins and wiring

    4.1 Use [wiring](https://raw.githubusercontent.com/petervflocke/ESP32Radio-V2PvF/master/Philips_DS1150/PhilipsESP32Radio.png) or

    4.2 Use [Config](https://github.com/petervflocke/ESP32Radio-V2PvF/blob/master/include/config.txt)

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

5. Do not connect anything else! Compile and upload the code to ESP32, turn on serial monitoring, find out on the serial console your local IP ESP was granted from your DHCP/router.

6. Open IP address of your newly started ESP32Radio in your internet browser, go to Config page and paste the content of the [config file](https://github.com/petervflocke/ESP32Radio-V2PvF/blob/master/include/config.txt) file. Update your WiFi SSID/password there. Save it.

7. Restart Module, and monitor your serial console, if got a reasonable output, without any unexpected error messages, try to open webpage based on the IP address from the serial console.

8. For troubleshooting, etc. check the manual or open an issue.

9. Restart and check if the radio can connect to WiFi and any radio station. You can control the radio over a webpage - you don't need display and any keys

10. If 9 works you can start to disassemble Philips docking station and modify it

11. Carefully rescue some part from the original PCB like Electrolytic capacitor, jst connectors, bottom LED and top pcb with keys and of course speakers.

12. Use the original pcb to cut out from a universal PCB basis for your elements. Check how to place them on the board. You can use [my pictures](https://github.com/petervflocke/ESP32Radio-V2PvF/tree/master/Philips_DS1150) as this works fine and at the end you will be able to close the original enclosure.

13. For the OLED Display you can use [this enclosure](https://www.thingiverse.com/thing:2176764). and For the Encoder Knob for example one of [these](EncoderKnobs.stl).

14. Tricky steps:

    14.1 Add / glue a micro female connector to the Philips enclosure, connect only ground, D+, D- leave the plus/VBUS (see wiring) unconceded. I glued it to the original PCB next to power socket.

    14.2 Solder a female micro usb connector to a cable ribbon and create an extension from ESP32 USB to an outside of the box. Check this [picture](https://raw.githubusercontent.com/petervflocke/ESP32Radio-V2PvF/master/Philips_DS1150/IMG20230204121923.jpg) for some inspiration.
    
    14.3 To open upper part use some hot air to carefully unglue the sticker. Try to mount the encoder in the middle, some plastic cutting will be necessary. 

    14.4 Glue an universal PCB with two tactile switches for boot and reset to the Philips key PCB
    
    14.4 Use again hot air to glue the sticker back once you are done.
    
    14.5 Think if you want to add the light sensor rather to the OLED display than here. I will do this in the next version (maybe).

15. Solder all together and enjoy

Feel free to ask any question, I can extend this basic description with more details if needed.
