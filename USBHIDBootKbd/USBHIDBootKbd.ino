#include <hidboot.h>
#include <usbhub.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

// libs e definicao do display
/*
  Lcd pins:
    Arduino Uno: A5, A4

  cable colors:
    yellow: A5
    Green: A4
*/
#include <LiquidCrystal_I2C.h>
#define I2C_ADDR 0x27
LiquidCrystal_I2C lcd(I2C_ADDR, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display


// instancia do usb
USB     Usb;
HIDBoot<USB_HID_PROTOCOL_KEYBOARD>    HidKeyboard(&Usb);

/*
  normal: 0
  encrypt: 1
  decrypt: 2
*/
int modeProgram = 0, scroll = 0;
String message = "", messagemInput = "";
const char *str;
char character = '\0';

class KbdRptParser : public KeyboardReportParser {

  protected:
    void OnKeyDown	(uint8_t mod, uint8_t key);
//    void OnKeyPressed(uint8_t key);
};

KbdRptParser Prs;

void KbdRptParser::OnKeyDown(uint8_t mod, uint8_t key)
{
  uint8_t c = OemToAscii(mod, key);
  if (c && modeProgram == 0) {
    Serial.print((char)c);
  }
}

//void KbdRptParser::OnKeyPressed(uint8_t key)
//{
//  character = (char)key;
//};

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

  HidKeyboard.SetReportParser(0, &Prs);

  lcd.begin();
  lcd.backlight();
  lcd.clear();
  showMode();
  lcd.noBacklight();
}

void loop()
{
  Usb.Task();
//  verifyCharacter();
  
  if (Serial.available() > 0)
  {
    messagemInput = Serial.readString();
    printLCD(messagemInput);
    if (messagemInput.substring(0, 6) == "[MODE]")
    {
      modeProgram = messagemInput.substring(6, 7).toInt();
      showMode();
    }
    if (messagemInput.substring(0, 8) == "[DECODE]" && modeProgram == 2)
    {
      decryptMessage(messagemInput.substring(8, messagemInput.length() - 1));
    }
    if (modeProgram == 2)
    {
      scrollKeyboard();
    }
  }
}

void verifyCharacter(){
  if (character != '\0'){
    Serial.print(character);
    character = '\0';
  }
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

void encrypt()
{
  // otherwise, just print all normal characters
  // check for some of the special keys
  //    if (c == PS2_ENTER)
  //    {
  //      str = message.c_str();
  //      rot47(str);
  //      Serial.print(message);
  //      message = "";
  //    }
  //    else if (c == PS2_LEFTARROW)
  //    {
  //      setScrollNumber(-1, message.length());
  //    }
  //    else if (c == PS2_RIGHTARROW)
  //    {
  //      setScrollNumber(1, message.length());
  //    }
  //    else if (c == PS2_DELETE)
  //    {
  //      if (message.length() > 0)
  //      {
  //        message = message.substring(0, message.length() - 1);
  //        lcd.clear();
  //      }
  //    }
  //    else
  //    {
  //      // otherwise, just print all normal characters
  //      message += c;
  //    }
  //  }
}

void scrollKeyboard()
{
  // otherwise, just print all normal characters
  // check for some of the special keys
  //    if (c == PS2_LEFTARROW)
  //    {
  //      setScrollNumber(-1, message.length());
  //    }
  //    else if (c == PS2_RIGHTARROW)
  //    {
  //      setScrollNumber(1, message.length());
  //    }
}

void setScrollNumber(int number, int lengthString)
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
  rot47(str);
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
