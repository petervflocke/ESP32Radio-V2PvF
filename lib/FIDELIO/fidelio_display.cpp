#include "fidelio_display.h"
#include <SPI.h>
#include <string.h>

word FidelioDisplay::numbers[] = {0x3F00, 0x0600, 0x5B00, 0x4F00, 0x6600, 0x6D00, 0x7D00, 0x0700, 0x7F00, 0x6F00}; //0..9
byte FidelioDisplay::daddr[]   = {0xC6, 0xC4, 0xC2, 0xC0};
// byte FidelioDisplay::daddr[]   = {0xC0, 0xC2, 0xC4, 0xC6};

// namespace PT6964 {

FidelioDisplay::FidelioDisplay() {
  displaySPI = new SPIClass();
}

void FidelioDisplay::init(int dioPin, int clkPin, int stbPin, uint32_t spiClk) 
{
  _dioPin = dioPin;
  _clkPin = clkPin;
  _stbPin = stbPin;
  _spiClk = spiClk;
  _dots = false;
  _pm = false;
  _alarm = false;
  displaySPI->begin(_clkPin, -1, _dioPin, _stbPin);
  pinMode(displaySPI->pinSS(), OUTPUT);
  delay(250);
  sendCommand(CMD_MODE_WRITE_INCREMENT);  // Defualt write increament addr
  sendCommand(CMD_DISPLAY_4x13);          // Configur as 4Dig 13Seg
  cls();
  setBright(7);
  roti = 1;
}

void FidelioDisplay::setBright(int level)
{
  sendCommand(CMD_DISPLAY_ON | (level & CMD_DISPLAY_ON_MASK) );
}

void FidelioDisplay::Off()
{
  sendCommand(CMD_DISPLAY_OFF);
}

void FidelioDisplay::cls()
{
  _dots = false;
  _pm = false;
  _alarm = false;
  sendCommand(CMD_MODE_WRITE_INCREMENT);
  spiStart();
  sendByte(CMD_SET_ADDR_0);    // 3: Set address to 00 / first
  for(int i = 0; i < 4; i++) { // clear display memory (4 digits)
    sendWord(0x0000);
  }
  spiStop();
}


 void FidelioDisplay::dots(bool value)
 {
  _dots = value;
 }
 
 void FidelioDisplay::pm(bool value)
 {
  _pm = value;
 }
 
 void FidelioDisplay::alarm(bool value)
 {
  _alarm = value;
 }

 void FidelioDisplay::toogleDots()
 {
  _dots = !_dots;
 }
 
 void FidelioDisplay::tooglePm()
 {
  _pm = !_pm;
 }
 
 void FidelioDisplay::toogleAlarm()
 {
  _alarm = !_alarm;
 }

void FidelioDisplay::print(char *buf)
{ word data;
  char ch;
  sendCommand(CMD_MODE_WRITE_FIXED_ADDRESS);
  for (int i = 0; i < 4; i++)  {
    ch = buf[i];
    if (ch == 0) break;
    if (ch < '0' || ch > '9') {
      data = 0x00 + daddr[i]; // not covered by 7segments font => empty
    } else {
      data = numbers[buf[i] - '0'] + daddr[i];
    }
    if (_dots  && i == 1) data |= 0x8000;
    if (_alarm && i == 2) data |= 0x8000;
    if (_pm    && i == 3) data |= 0x8000;
    spiStart();
    sendWord(data);
    spiStop();
  }
}

void FidelioDisplay::draw(byte pos, byte what)
{
  if (pos > 4) return;
  sendCommand(CMD_MODE_WRITE_FIXED_ADDRESS);
  // sendByte(daddr[pos]);    // 3: Set address to 00 / first  
  word data = (what << 8) + daddr[pos];
  if (_dots  && pos == 1) data |= 0x8000;
  if (_alarm && pos == 2) data |= 0x8000;
  if (_pm    && pos == 3) data |= 0x8000;
  spiStart();
  sendWord(data);
  spiStop();
}

void FidelioDisplay::sendByte(byte data) {
  displaySPI->transfer(data);
}

void FidelioDisplay::sendWord(word data) {
  displaySPI->transfer(byte(data & 0xFF));
  displaySPI->transfer(byte(data >> 8));  
}

void FidelioDisplay::spiStart() {
  displaySPI->beginTransaction(SPISettings(_spiClk, LSBFIRST, SPI_MODE1));
  digitalWrite(_stbPin, LOW);
}
void FidelioDisplay::spiStop() {
  digitalWrite(_stbPin, HIGH);
  displaySPI->endTransaction();
}

void FidelioDisplay::sendCommand(byte data) {
  spiStart();
  sendByte(data);
  spiStop();
  delayMicroseconds(1);
}


/****************** ESP32Radio Specific function ******************/

void FidelioDisplay::updateTime (const char* str) {
  static char oldstr[9] = "XX:XX:XX";            // For compare
  uint8_t     i,j;                               // Indexs in strings
  char        ch;                                // character
  char        output[5]="::::";

  if ( millis() - startDelay >= DELAYUPDATE)  {   // Don't try to frequently
    startDelay = 0;
    if (strcmp(str, oldstr) != 0) {
      toogleDots();
      i = 0;
      j = 0;
      while ( (i < 6) && (ch=str[i]) ) {
        if ( ch >= '0' && ch <= '9') {
          if (0 == i && '0' == ch)
            output[j] = ':';
          else
            output[j] = ch;
          j += 1;
        }
        i += 1;
      }
      print(output);
    }
  } else {
    draw(0, 0);
  }
}

void FidelioDisplay::updateVolume (int vol) {
  char output[5]=" 100";

  dots(false);
  if (100 == vol) {
    print(output);
  } else {
    output[1] = ':';
    output[2] = '0' + vol / 10;
    output[3] = '0' + vol % 10;
    print(output);
  }
  draw(0, roti1Elements[roti]);
  roti = (roti+1) % roti1Numbers;
}

void FidelioDisplay::updateStation (int station) {
  char output[5]="    "; 

  dots(true);
  if (station > 9) {
    output[2] = '0' + station / 10;
  }
  output[3] = '0' + station % 10;
  print(output);
  draw(1, 9+128); // -> a|d|:

  draw(0, roti2Elements[roti]);
  roti = (roti+1) % roti1Numbers;
}

