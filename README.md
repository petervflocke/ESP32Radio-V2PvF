# ESP32Radio-V2PvF

Forked and based on the excellent code https://github.com/Edzelf/ESP32Radio-V2 from Ed Smallenburg aka Edzelf
For details refer to above repo or check doc folder.

This fork was created to modify Philips DS1150/12 into an Internet radio using the existing seven-segment display, keys and built in bottom LEDs as well as extend it with an OLED and rotary encoder.

If you are here for a vanilla ESP32 Internet Radio go to the origin code from Edzelf


## Philips DS1150/12 into Internet Radio HowTo?
Usefull links in this repo:
- [Cookbook](Philips_DS1150/README.md) from my modification.
- [Wiring](Philips_DS1150/PhilipsESP32Radio.png) of this mod.
- [Working Config](include/config.txt).

## Youtube quick demo:
[![Youtube quick demo](https://img.youtube.com/vi/QBrp1FDthUw/0.jpg)](https://www.youtube.com/watch?v=QBrp1FDthUw "Youtube quick demo")


## PfV Refactoring Scope (so far):
Most differences from the original code:

- added Philips DS1150/12 PT6964 display driver on a dedicated SPI
    - new config params: pin_stb_out, pin_clk_out, pin_dio_out
- added Philips DS1150/12 button LED driver
    - new config params: pin_led_out
- added Philips DS1150/12 analog 4 buttons scan procedure and config
    - reserved GPIO 35
    - new command for the analog buttons defined see readAnalogButtons() for details
- added light sensor (photo resistor) to drive fidelio display brightens
    - reserved GPIO 39
- added in include/config.h two parameters:
    - SCANDIGITAL to enable / disable digital pins scan (not used in my version since there is no digital keys)
    - SCANANALOG to enable / disable analog scan of the resistor based 4 keys (from Philips DS1150), config similar to Touch pins
- added new command `toggle` to stop/start the radio. Unlike the long press on rotary encoder to stop only. 
- added new command `bleds` to rotate LED brightness at the Fidelio bottom
- change Rotary Encoder handling && OLED1306 handling
    - immediate Volume update
    - proper radio station names refresh
    - introduced forced station name. Instead of getting icyname from stream, you can force to display name from the settings e.g.:

    ```
    preset_00 = stream.abcd   #  0 Radio ABC
    preset_01 = stream.efgh   #! 1 Radio 123
    ```

    -   Station 1 will have default name "Radio 123" independent from the icystream name. This can be forced by adding `!` just after the `#`

