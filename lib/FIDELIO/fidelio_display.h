#ifndef FIDELIODISPLAY_h
#define FIDELIODISPLAY_h

#include <Arduino.h>
#include <SPI.h>

/*
 1  -- 
32 |  |2
64  --
16 |  |4
 8  --  .128

a =  1
b =  2
c =  4
d =  8
e = 16
f = 32
g = 64
h = 128

Pinout at fidelio-display
1 GND
2 VCC
3 stbPin => 15
4 clkPin => 14
5 dioPin => 13
*/

/* additional ESP32Radio functions */
#define DELAYUPDATE 4000 /* delay in miliseconds */
/***********************************/

class FidelioDisplay
{
public:
  FidelioDisplay();
  void init(int dioPin, int clkPin, int stbPin, uint32_t spiClk);
  void cls();
  void print(char *buf);
  void draw(byte pos, byte what);
  void Off();
  void setBright(int level);
  void dots(bool value);
  void pm(bool value);
  void alarm(bool value);
  void toogleDots();
  void tooglePm();
  void toogleAlarm();

  /* additional ESP32Radio functions */
  /* ToDo: to satisfy my and c++ purist create a new object and extend the fidelo class */
  void updateTime (const char*);
  void updateVolume (int);
  void updateStation (int);
  
  inline void setStartDelay(u_int32_t val) {
    startDelay = val;
  }

private:
    static const uint8_t CMD_MODE_WRITE_INCREMENT     = 0b01000000;
    static const uint8_t CMD_MODE_WRITE_FIXED_ADDRESS = 0b01000100;
    static const uint8_t CMD_SET_ADDR_0 = 0xC0;
    static const uint8_t CMD_DISPLAY = 0x80;
    static const uint8_t CMD_DISPLAY_OFF = CMD_DISPLAY;
    static const uint8_t CMD_DISPLAY_ON = CMD_DISPLAY | 0x08;
    static const uint8_t CMD_DISPLAY_ON_MASK = 0b00000111;
    static const uint8_t CMD_DISPLAY_4x13 = 0b00000000;
    // static const uint8_t CMD_DISPLAY_7x10 = 0b00000011;

  SPIClass *displaySPI;

  void sendByte(byte data);
  void sendWord(word data);
  void spiStart();
  void spiStop();
  void sendCommand(byte data);

  int _dioPin, _clkPin, _stbPin;
  uint32_t _spiClk;
  bool _pm, _alarm, _dots;
  long _tLastTime;
  static word numbers[];
  static byte daddr[];

  /* additional ESP32Radio functions */
  u_int32_t startDelay;  // set to the future 
  byte roti; // rotery animation
  
  #define roti1Numbers 3
  const int8_t roti1Elements[roti1Numbers] = {8, 72, 73};
  const int8_t roti2Elements[roti1Numbers] = {8, 64,  1};
};

#endif
