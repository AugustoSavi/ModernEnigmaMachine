#include <KeyboardController.h>

// Initialize USB Controller
USBHost usb;

// Attach Keyboard controller to USB
KeyboardController keyboard(usb);

void setup(){
  Serial.begin(9600);
}

void loop(){
  usb.Task();
}

void keyPressed() {
  Serial.print("Pressed:  ");
  Serial.print(keyboard.getKey());
  Serial.println();
}
