/*  PS2Keyboard library example
  
  PS2Keyboard now requries both pins specified for begin()

  keyboard.begin(data_pin, irq_pin);
  
  Valid irq pins:
    Arduino Uno:  2, 3
    Arduino Due:  2, 3

  cable colors:
    White: 2
    Green: 3
*/
   
#include <PS2Keyboard.h>

const int DataPin = 2;
const int IRQpin =  3;

PS2Keyboard keyboard;

void setup() {
  delay(2000);
  keyboard.begin(DataPin, IRQpin, PS2Keymap_Brazil);
  Serial.begin(115200);
}

void loop() {
  if (keyboard.available()) {
    // read the next key
    char c = keyboard.read();
      // otherwise, just print all normal characters
    // check for some of the special keys
     if (c == PS2_ESC) {
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
    } else {
      // otherwise, just print all normal characters
      Serial.print(c);
    }
  }

//  if (Serial.available() > 0){
//      Serial.println(Serial.readString());
//    }
  
}
