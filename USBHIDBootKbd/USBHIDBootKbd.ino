#include <hidboot.h>
//#include <usbhub.h>
#include <LiquidCrystal_I2C.h>

#define I2C_ADDR 0x27 // Arduino COM SHIELD
LiquidCrystal_I2C lcd(I2C_ADDR, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display
String message = "", messagemInput = "";
const char *str;

/*
  normal: 0
  encrypt: 1
  decrypt: 2
*/
int modeProgram = 1, scroll = 0;

// Satisfy the IDE, which needs to see the include statement in the ino too.
//#ifdef dobogusinclude
//#include <spi4teensy3.h>
//#endif
//#include <SPI.h>

uint8_t UPARROW_KEYBOARD = 82;
uint8_t RIGTHARROW_KEYBOARD = 79;
uint8_t DOWNARROW_KEYBOARD = 81;
uint8_t LEFTARROW_KEYBOARD = 80;
uint8_t DELETE_KEYBOARD = 42;
uint8_t ENTER_KEYBOARD = 40;
uint8_t TAB_KEYBOARD = 43;
uint8_t ESC_KEYBOARD = 41;

class KbdRptParser : public KeyboardReportParser
{
    void normalKeyboard(uint8_t mod, uint8_t key);
    void encrypt(uint8_t mod, uint8_t key);
    void printLCD(String message);
    void scrollKeyboard(uint8_t key);
    char rot47(char *s);
    void setScrollNumber(int number, int lengthString);

  protected:
    void OnKeyDown	(uint8_t mod, uint8_t key);
    void OnKeyPressed(uint8_t mod, uint8_t key);
};

void KbdRptParser::OnKeyDown(uint8_t mod, uint8_t key)
{
  OnKeyPressed(mod, key);
}

void KbdRptParser::OnKeyPressed(uint8_t mod, uint8_t key)
{
  if (modeProgram == 0)
  {
    normalKeyboard(mod, key);
  }
  else if (modeProgram == 1)
  {
    encrypt(mod, key);
    printLCD(message);
  }
  else if (modeProgram == 2)
  {
    scrollKeyboard(key);
  }
};

void KbdRptParser::normalKeyboard(uint8_t mod, uint8_t key)
{
  uint8_t c = OemToAscii(mod, key);

  // check for some of the special keys
  if (key == ENTER_KEYBOARD)
  {
    Serial.print("[Enter]");
  }
  else if (key == TAB_KEYBOARD)
  {
    Serial.print("[Tab]");
  }
  else if (key == ESC_KEYBOARD)
  {
    Serial.print("[ESC]");
  }
  else if (key == DOWNARROW_KEYBOARD)
  {
    Serial.print("[PgDn]");
  }
  else if (key == UPARROW_KEYBOARD)
  {
    Serial.print("[PgUp]");
  }
  else if (key == LEFTARROW_KEYBOARD)
  {
    Serial.print("[Left]");
  }
  else if (key == RIGTHARROW_KEYBOARD)
  {
    Serial.print("[Right]");
  }
  else if (key == UPARROW_KEYBOARD)
  {
    Serial.print("[Up]");
  }
  else if (key == DOWNARROW_KEYBOARD)
  {
    Serial.print("[Down]");
  }
  else if (key == DELETE_KEYBOARD)
  {
    Serial.print("[Backspace]");
  }
  //    else if (key == PS2_F1)
  //    {
  //      Serial.print("[F1]");
  //    }
  else
  {
    if (c) {
      Serial.print((char)c);
    }
  }
}

void KbdRptParser::encrypt(uint8_t mod, uint8_t key)
{
  uint8_t c = OemToAscii(mod, key);
  // otherwise, just print all normal characters
  // check for some of the special keys
  if (key == ENTER_KEYBOARD)
  {
    str = message.c_str();
    rot47(str);
    Serial.print(message);
    message = "";
    lcd.clear();
  }
  else if (key == LEFTARROW_KEYBOARD)
  {
    setScrollNumber(-1, message.length());
  }
  else if (key == RIGTHARROW_KEYBOARD)
  {
    setScrollNumber(1, message.length());
  }
  else if (key == DELETE_KEYBOARD)
  {
    if (message.length() > 0)
    {
      message = message.substring(0, message.length() - 1);
      lcd.clear();
    }
  }
  else
  {
    if (c) {
      // otherwise, just print all normal characters
      message += (char)c;
    }

  }
}

char KbdRptParser::rot47(char *s)
{
  char *p = s;
  while (*p)
  {
    if (*p >= '!' && *p <= 'O')
      *p = ((*p + 47) % 127);
    else if (*p >= 'P' && *p <= '~')
      *p = ((*p - 47) % 127);
    p++;
  }
  return s;
}

void KbdRptParser::scrollKeyboard(uint8_t key)
{
  //     otherwise, just print all normal characters
  //     check for some of the special keys
  if (key == LEFTARROW_KEYBOARD)
  {
    setScrollNumber(-1, message.length());
  }
  else if (key == RIGTHARROW_KEYBOARD)
  {
    setScrollNumber(1, message.length());
  }
}

void KbdRptParser::setScrollNumber(int number, int lengthString)
{
  if ((lengthString + scroll + number) > lengthString)
  {
    return;
  }
  else if ((lengthString + scroll + number) < 32)
  {
    return;
  }
  else
  {
    scroll += number;
  }
}

void KbdRptParser::printLCD(String message)
{
  int messageLength = message.length();

  if (messageLength <= 16)
  {
    lcd.setCursor(0, 0);
    lcd.print(message);
  }
  else if (messageLength > 16 && messageLength <= 32)
  {
    lcd.setCursor(0, 0);
    lcd.print(message);
    lcd.setCursor(0, 1);
    lcd.print(message.substring(16, messageLength));
  }
  else if (messageLength > 32)
  {
    lcd.setCursor(0, 0);
    lcd.print(message.substring(messageLength - 32 + scroll, messageLength - 16 + scroll));
    lcd.setCursor(0, 1);
    lcd.print(message.substring(messageLength - 16 + scroll, messageLength + scroll));
  }
}

void printLCD(String message)
{
  int messageLength = message.length();

  if (messageLength <= 16)
  {
    lcd.setCursor(0, 0);
    lcd.print(message);
  }
  else if (messageLength > 16 && messageLength <= 32)
  {
    lcd.setCursor(0, 0);
    lcd.print(message);
    lcd.setCursor(0, 1);
    lcd.print(message.substring(16, messageLength));
  }
  else if (messageLength > 32)
  {
    lcd.setCursor(0, 0);
    lcd.print(message.substring(messageLength - 32 + scroll, messageLength - 16 + scroll));
    lcd.setCursor(0, 1);
    lcd.print(message.substring(messageLength - 16 + scroll, messageLength + scroll));
  }
}

void showMessageLcd(String message)
{
  lcd.clear();
  printLCD(message);
  delay(2000);
  lcd.clear();
}

void decryptMessage(String message)
{
  lcd.clear();
  str = message.c_str();
  //  rot47(str);
  printLCD(str);
}

char rot47(char *s)
{
  char *p = s;
  while (*p)
  {
    if (*p >= '!' && *p <= 'O')
      *p = ((*p + 47) % 127);
    else if (*p >= 'P' && *p <= '~')
      *p = ((*p - 47) % 127);
    p++;
  }
  return s;
}

void showMode()
{
  if (modeProgram == 0)
  {
    lcd.backlight();
    showMessageLcd("Modo selecionado: normal");
    lcd.noBacklight();
  }
  else if (modeProgram == 1)
  {
    lcd.backlight();
    showMessageLcd("Modo selecionado: encrypt");
  }
  else if (modeProgram == 2)
  {
    lcd.backlight();
    showMessageLcd("Modo selecionado: decrypt");
  }
}

USB     Usb;
HIDBoot<USB_HID_PROTOCOL_KEYBOARD>    HidKeyboard(&Usb);

KbdRptParser Prs;

void setup()
{
  Serial.begin( 115200 );
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif
  Serial.println("Start");

  if (Usb.Init() == -1)
    Serial.println("OSC did not start.");

  delay( 200 );

  lcd.begin(); // initialize the lcd
  lcd.backlight();
  lcd.clear();
  showMode();

  HidKeyboard.SetReportParser(0, &Prs);
}

void loop()
{
  if (Serial.available() > 0)
  {
    messagemInput = Serial.readString();
    if (messagemInput.substring(0, 6) == "[MODE]")
    {
      modeProgram = messagemInput.substring(6, 7).toInt();
      showMode();
    }
    if (messagemInput.substring(0, 8) == "[DECODE]" && modeProgram == 2)
    {
      decryptMessage(messagemInput.substring(8, messagemInput.length() - 1));
    }
  }

  Usb.Task();
}
