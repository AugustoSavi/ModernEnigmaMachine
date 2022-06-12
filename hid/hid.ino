#include <Keyboard.h>
#include <PS2Keyboard.h>


const int DataPin = 2;
const int IRQpin =  3;

// use this option for OSX.
// Comment it out if using Windows or Linux:
// char ctrlKey = KEY_LEFT_GUI;
// use this option for Windows and Linux.
// leave commented out if using OSX:
char ctrlKey = KEY_LEFT_CTRL;

PS2Keyboard externalKeyboard;


void setup() {
  delay(5000);
  
  // initialize control over the keyboard:
  Keyboard.begin();
  
  externalKeyboard.begin(DataPin, IRQpin);

  Serial.begin(9600);
  Serial.println("Keyboard Test:");
}

void loop() {
  if (externalKeyboard.available()) {
    
    // read the next key
    char c = externalKeyboard.read();
    
    // check for some of the special keys
    if (c == PS2_ENTER) {
      Serial.println();
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
      Keyboard.println("teste");
      Keyboard.releaseAll();
    } else if (c == PS2_DOWNARROW) {
      Serial.print("[Down]");
    } else if (c == PS2_DELETE) {
      Serial.print("[Del]");
    } else {
      
      // otherwise, just print all normal characters
      Serial.println(c);
    }
  }
}
