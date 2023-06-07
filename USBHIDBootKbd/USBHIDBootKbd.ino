#include <hidboot.h>
#include <LiquidCrystal_I2C.h>

#define I2C_ADDR 0x27

#define UPARROW_KEYBOARD 82
#define RIGTHARROW_KEYBOARD 79
#define DOWNARROW_KEYBOARD 81
#define LEFTARROW_KEYBOARD 80
#define DELETE_KEYBOARD 42
#define ENTER_KEYBOARD 40
#define TAB_KEYBOARD 43
#define ESC_KEYBOARD 41

LiquidCrystal_I2C lcd(I2C_ADDR, 16, 2);
String message = "", messagemInput = "";
const char *str;

/*
  normal: 0
  encrypt: 1
  decrypt: 2
*/
int modeProgram = 0, scroll = 0;

class KbdRptParser : public KeyboardReportParser
{
    void normalKeyboard(uint8_t mod, uint8_t key);
    void encrypt(uint8_t mod, uint8_t key);
    void printLCD(String message);
    String rot47(String input);
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
  switch (modeProgram) {
    case 0:
      normalKeyboard(mod, key);
      break;
    case 1:
      encrypt(mod, key);
      printLCD(message);
      break;
    case 2:
      if (key == LEFTARROW_KEYBOARD)
      {
        setScrollNumber(-1, message.length());
      }
      else if (key == RIGTHARROW_KEYBOARD)
      {
        setScrollNumber(1, message.length());
      }
      printLCD(message);
      break;
  }
};

void KbdRptParser::normalKeyboard(uint8_t mod, uint8_t key)
{
  uint8_t c = OemToAscii(mod, key);

  switch (key) {
    case ENTER_KEYBOARD:
      Serial.print("[Enter]");
      break;
    case TAB_KEYBOARD:
      Serial.print("[Tab]");
      break;
    case ESC_KEYBOARD:
      Serial.print("[ESC]");
      break;
    case LEFTARROW_KEYBOARD:
      Serial.print("[Left]");
      break;
    case RIGTHARROW_KEYBOARD:
      Serial.print("[Right]");
      break;
    case UPARROW_KEYBOARD:
      Serial.print("[Up]");
      break;
    case DOWNARROW_KEYBOARD:
      Serial.print("[Down]");
      break;
    case DELETE_KEYBOARD:
      Serial.print("[Backspace]");
      break;
    default:
      if (c) {
        Serial.print((char)c);
      }
      break;
  }
}

void KbdRptParser::encrypt(uint8_t mod, uint8_t key)
{
  uint8_t c = OemToAscii(mod, key);
  switch (key) {
    case ENTER_KEYBOARD:
      Serial.print(rot47(message));
      message = "";
      lcd.clear();
      break;
    case LEFTARROW_KEYBOARD:
      setScrollNumber(-1, message.length());
      break;
    case RIGTHARROW_KEYBOARD:
      setScrollNumber(1, message.length());
      break;
    case DELETE_KEYBOARD:
      if (message.length() > 0)
      {
        message = message.substring(0, message.length() - 1);
        lcd.clear();
      }
      break;
    default:
      if (c) {
        if(message.length() <= 200){
          message += (char)c;
        }
      }
      break;
  }
}

String KbdRptParser::rot47(String input) {
  String table = "`!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_abcdefghijklmnopqrstuvwxyz{|}~";
  String output = "";

  for (char& _char : input) {
    int index = table.indexOf(_char);
    if (index != -1) {
      output += table[(index + 47) % 94];
    } else {
      output += _char;
    }
  }

  return output;
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

void decryptMessage(String message_will_be_decrypt)
{
  lcd.clear();
  message = rot47_decode(message_will_be_decrypt);
  printLCD(message);
}

String rot47_decode(String input)
{
  String table = "`!\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_abcdefghijklmnopqrstuvwxyz{|}~";
  String output = "";

  for (char& _char : input) {
    int index = table.indexOf(_char);
    if (index != -1) {
      output += table[(index + 47) % 94];
    } else {
      output += _char;
    }
  }
  return output;
}

void showMode()
{
  switch (modeProgram) {
    case 0:
      lcd.backlight();
      showMessageLcd("Modo selecionado: normal");
      lcd.noBacklight();
      break;
    case 1:
      lcd.backlight();
      showMessageLcd("Modo selecionado: encrypt");
      break;
    case 2:
      lcd.backlight();
      showMessageLcd("Modo selecionado: decrypt");
      break;
  }
}

USB     Usb;
HIDBoot<USB_HID_PROTOCOL_KEYBOARD>    HidKeyboard(&Usb);
KbdRptParser Prs;

void setup()
{
  Serial.begin( 115200 );
#if !defined(__MIPSEL__)
  while (!Serial);
#endif
  Serial.println("Start");

  if (Usb.Init() == -1)
    Serial.println("OSC did not start.");

  delay( 200 );

  lcd.begin();
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
      message = "";
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
