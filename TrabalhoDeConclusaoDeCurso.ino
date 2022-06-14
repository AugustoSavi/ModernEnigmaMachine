/*  PS2Keyboard library example
  
  PS2Keyboard now requries both pins specified for begin()

  keyboard.begin(data_pin, irq_pin);
  
  Valid irq pins:
    Arduino Uno:  2, 3
    Arduino Due:  2, 3

  cable colors:
    White: 2
    Green: 3

    ------------------------------------
  Lcd pins:
    Arduino Uno: A5, A4

  cable colors:
    yellow: A5
    Green: A4
    
*/
   
#include <PS2Keyboard.h>
#include <LiquidCrystal_I2C.h>

#define I2C_ADDR 0x27

LiquidCrystal_I2C lcd(I2C_ADDR,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
PS2Keyboard keyboard;

const int DataPin = 2;
const int IRQpin =  3;
String message = "", messagemInput = "";

/*
normal: 0
encrypt: 1
decrypt: 2
*/
int modeProgram = 2;


void setup() {
  delay(2000);
  keyboard.begin(DataPin, IRQpin, PS2Keymap_Brazil);
  Serial.begin(115200);

  lcd.begin();   // initialize the lcd 
  
  // Print a message to the LCD.
  lcd.backlight();

  lcd.clear();

  showMessageLcd("modo selecionado: " + String(modeProgram));
}

void loop() {
  if(modeProgram == 0 ){
    normalKeyboard();
  }
  else if (modeProgram == 1){
    encrypt();
    printLCD(message);
  }
  
  if (Serial.available() > 0){
      messagemInput = Serial.readString();
      printLCD(messagemInput);
      if (messagemInput.substring(0, 6) == "[MODE]"){
        modeProgram = messagemInput.substring(6, 7).toInt();
        if(modeProgram == 0){ 
          showMessageLcd("Modo selecionado: normal");
         }
        else if (modeProgram == 1){
          showMessageLcd("Modo selecionado: encrypt");
         }
         else if (modeProgram == 2){
          showMessageLcd("Modo selecionado: decrypt");
         }
        
      }
      if (messagemInput.substring(0, 8) == "[DECODE]" && modeProgram == 2){
        decryptMessage(messagemInput.substring(8, messagemInput.length()));
      }
   }
  
}

void normalKeyboard() {
  if (keyboard.available()) {
    
    // read the next key
    char c = keyboard.read();
    
    // check for some of the special keys
    if (c == PS2_ENTER) {
      Serial.print("[Enter]");
    } else if (c == PS2_TAB) {
      Serial.print("[Tab]");
    } else if (c == PS2_ESC) {
      Serial.print("[ESC]");
    } else if (c == PS2_PAGEDOWN) {
      Serial.print("[PgDn]");
    } else if (c == PS2_PAGEUP) {
      Serial.print("[PgUp]");
    } else if (c == PS2_LEFTARROW) {
      Serial.print("[Left]");
    } else if (c == PS2_RIGHTARROW) {
      Serial.print("[Right]");
    } else if (c == PS2_UPARROW) {
      Serial.print("[Up]");
    } else if (c == PS2_DOWNARROW) {
      Serial.print("[Down]");
    } else if (c == PS2_DELETE) {
      Serial.print("[Del]");
    } else if (c == PS2_F1) {
      Serial.print("[F1]");
    } 
    else {
      // otherwise, just print all normal characters
      Serial.print(c);
    }
  }
}

void encrypt() {
  if (keyboard.available()) {
    // read the next key
    char c = keyboard.read();
      // otherwise, just print all normal characters
    // check for some of the special keys
    if (c == PS2_ENTER) {
      Serial.print(message);
    } 
     else if (c == PS2_ESC) {
      message += "";
    } else if (c == PS2_PAGEDOWN) {
      message += "";
    } else if (c == PS2_PAGEUP) {
      message += "";
    } else if (c == PS2_LEFTARROW) {
      message += "";
    } else if (c == PS2_RIGHTARROW) {
      message += "";
    } else if (c == PS2_UPARROW) {
      message += "[Up]";
    } else if (c == PS2_DOWNARROW) {
      message += "[Down]";
    } else if (c == PS2_DELETE) {
      if(message.length() > 0) {
        message = message.substring(0, message.length()-1);
        lcd.clear();
      }
    } else {
      // otherwise, just print all normal characters
      message += c;
    }
  }
}

void decryptMessage(String message){
  lcd.clear();
  printLCD(message);
}

void printLCD(String message) {
  if (message.length() <= 16){
    lcd.setCursor(0,0);
    lcd.print(message);
  }
  else if(message.length() > 16 && message.length() <= 32) {
    lcd.setCursor(0,0);
    lcd.print(message);
    lcd.setCursor(0,1);
    lcd.print(message.substring(16,message.length()));
  }
  else if(message.length() > 32) {
    lcd.setCursor(0,0);
    lcd.print(message.substring(message.length()-64, message.length()-32));
    lcd.setCursor(0,1);
    lcd.print(message.substring(message.length()-16,message.length()));
  }
}

void showMessageLcd(String message){
  lcd.clear();
  printLCD(message);
  delay(1000);
  lcd.clear();
}